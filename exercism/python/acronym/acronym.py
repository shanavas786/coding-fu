def abbreviate(words):
    acronym = ""
    for word in words.split():
        word = word.strip(" _-")
        for subword in word.split("-"):
            if subword:
                acronym += subword[0]

    return acronym.upper()
