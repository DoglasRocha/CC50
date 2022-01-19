# calculates the correspondent grade of a given text, using the Coleman-Liau
# index
def main():
    text = input('Text: ')

    letters, words, sentences = count_letters_words_sentences(text)
    grade = calculate_grade(letters, words, sentences)

    if (grade < 1):
        print('Before Grade 1')

    elif (grade < 16):
        print(f'Grade {grade}')

    else:
        print('Grade 16+')


# counts the letters, words and sentences of a given text
def count_letters_words_sentences(text: str) -> tuple:
    letters = 0
    words = 1
    sentences = 0

    for c in range(len(text)):

        if (text[c].isalpha()):
            letters += 1

        elif (text[c].isspace()):
            words += 1

        # valid punctuations
        elif (text[c] == '.' or text[c] == '!' or text[c] == '?'):
            sentences += 1

    return letters, words, sentences


# using the Coleman-Liau index, calculates the grade of a text using the words per hundred words
# and senteces per hundred words
def calculate_grade(letters: int, words: int, sentences: int) -> int:
    hundred_words = words / 100
    l = letters / hundred_words
    s = sentences / hundred_words

    grade = .0588 * l - .296 * s - 15.8

    return round(grade)


main()