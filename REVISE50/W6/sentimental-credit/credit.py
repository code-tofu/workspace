### USING STRING APPROACH ###
import cs50

card_num = cs50.get_string("Number:")
luhn_double = []
luhn_sum = 0
# print(card_num[0:2])
AMEX = [32, 37]
MASTERCARD = range(51, 56)
VISA = "4"
# has to be either comparing string or comparing int


for i in range(len(card_num)-2, -1, -2):
    # calculation starts from 2 digit from the right.
    # range has to include last from right index hence -1
    luhn_double.append(int(card_num[i])*2)
for i in range(len(luhn_double)):
    luhn_sum += luhn_double[i] // 10 + luhn_double[i] % 10
for i in range(len(card_num)-1, -1, -2):
    luhn_sum += int(card_num[i])

# print(luhn_sum)
luhn_check = (luhn_sum % 10)
if ((luhn_check == 0) and (len(card_num) == 15) and (int(card_num[0:2])) in AMEX):
    print("AMEX")
elif ((luhn_check == 0) and (len(card_num) == 16 or len(card_num) == 13) and (card_num[0] is VISA)):
    print("VISA")
elif ((luhn_check == 0) and (len(card_num) == 16) and (int(card_num[0:2]) in MASTERCARD)):
    print("MASTERCARD")
else:
    print("INVALID")

"""




$ ./credit
Number: 4003-6000-0000-0014
Number: foo
Number: 4003600000000014
VISA

$ python credit.py
Number: 378282246310005
AMEX

"""