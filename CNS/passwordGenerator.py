# Using secret module write a python program to generate a strong password
# Find quality of the generated password using crypt tool

import random
import secrets
import string

UPPERCASE_MIN = 1
LOWERCASE_MIN = 1
DIGIT_MIN = 1
SPECIAL_MIN = 1

CHARACTERS = string.ascii_letters + string.digits + string.punctuation

password = ''
while (len(password) < (UPPERCASE_MIN + LOWERCASE_MIN + DIGIT_MIN + SPECIAL_MIN)):
    password += secrets.choice(string.ascii_uppercase)
    password += secrets.choice(string.ascii_lowercase)
    password += secrets.choice(string.digits)
    password += secrets.choice(string.punctuation)

while (len(password) < 17):
    password += secrets.choice(CHARACTERS)

password = ''.join(random.sample(password, len(password)))
 
print(password)