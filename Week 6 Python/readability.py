# TODO
from cs50 import get_string

text = get_string("TEXT: ").upper()
# count letters
count_letters = 0;
for i in text:
    if i >= "A" and i <= "Z":
        count_letters += 1

# count words
count_words = text.count(" ") + 1

# count sentences
count_sentences = text.count(".") + text.count("!") + text.count("?")

L = count_letters / count_words * 100
S = count_sentences / count_words * 100
index = round(0.0588 * L - 0.296 * S - 15.8)
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print("Grade", index)