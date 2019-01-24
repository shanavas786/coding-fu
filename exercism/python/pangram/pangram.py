from string import ascii_lowercase


def is_pangram(sentence):
    sentence = sentence.lower()
    for letter in ascii_lowercase:
        if letter not in sentence:
            return False

    return True
