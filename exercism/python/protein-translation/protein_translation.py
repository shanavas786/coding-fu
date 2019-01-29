MAPPER = {
    "AUG": "Methionine",
    "UUU": "Phenylalanine",
    "UUC": "Phenylalanine",
    "UUA": "Leucine",
    "UUG": "Leucine",
    "UCU": "Serine",
    "UCC": "Serine",
    "UCA": "Serine",
    "UCG": "Serine",
    "UAU": "Tyrosine",
    "UAC": "Tyrosine",
    "UGU": "Cysteine",
    "UGC": "Cysteine",
    "UGG": "Tryptophan",
}

STOP_CODONS = ["UAA", "UAG", "UGA"]


def tokenize(strand):
    return iter([strand[i : i + 3] for i in range(0, len(strand), 3)])


def proteins(strand):
    polypeptide = []
    for codon in tokenize(strand):
        if codon in STOP_CODONS:
            break
        polypeptide.append(MAPPER[codon])

    return polypeptide
