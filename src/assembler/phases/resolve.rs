use super::types::BinaryElement;
use crate::common;
use crate::spec::types::hw::*;
use std::collections::HashMap;
use std::{convert::TryFrom, fmt::Display};

#[derive(Debug, PartialEq, Eq)]
pub enum Error {
    DuplicateLabel(String),
    UnknownLabel(String),
}

impl Display for Error {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Error::DuplicateLabel(label) => write!(f, "Duplicate definition of label: '{}'", label),
            Error::UnknownLabel(label) => write!(f, "Use of undefined label: '{}'", label),
        }
    }
}

impl BinaryElement {
    fn words(&self) -> usize {
        match self {
            BinaryElement::LabelDef(_) => 0,
            BinaryElement::Data(raw) => raw.len(),
            BinaryElement::Inst(blob) => blob.words(),
        }
    }

    fn resolve<F>(self, resolver: F) -> Result<Vec<Word>, Error>
    where
        F: Fn(String) -> Result<Word, Error>,
    {
        match self {
            BinaryElement::LabelDef(_) => Ok(vec![]),
            BinaryElement::Data(raw) => Ok(raw),
            BinaryElement::Inst(blob) => blob.resolve(resolver),
        }
    }
}

fn build_label_map(elems: &[BinaryElement]) -> Result<HashMap<String, Word>, Error> {
    let mut label_map = HashMap::new();

    let mut bs = 0;
    for e in elems {
        if let BinaryElement::LabelDef(label) = e {
            if label_map
                .insert(label.clone(), Word::try_from(bs).unwrap())
                .is_some()
            {
                return Err(Error::DuplicateLabel(label.clone()));
            }
        }

        bs += 2 * e.words();
    }

    Ok(label_map)
}

pub fn resolve(elems: Vec<BinaryElement>) -> Result<Vec<Word>, Error> {
    let label_map = build_label_map(&elems)?;
    let label_resolver = |tag| label_map.get(&tag).copied().ok_or(Error::UnknownLabel(tag));

    common::accumulate_vecs(elems.into_iter().map(|be| be.resolve(label_resolver)))
}
