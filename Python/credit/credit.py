def main() -> None:
    credit_card = get_credit_card()
    
    if (has_valid_length(credit_card) 
        & has_valid_number(credit_card)):
        
        if (is_visa(credit_card)):
            print('VISA')
            
        elif (is_amex(credit_card)):
            print('AMEX')
            
        elif (is_master(credit_card)):
            print('MASTERCARD')
            
        else:
            print('INVALID')
    
    else:
        print('INVALID')


def get_credit_card() -> str:
    card_number = input('Credit card number: ')
    
    if (len(card_number) > 0):
        return card_number
        
    return get_credit_card()
    

def has_valid_length(card_number: str) -> bool:
    
    return (len(card_number) >= 13)
    
    
def has_valid_number(card_number: str) -> bool:
    
    even = int(card_number) % 2 == 0
    
    is_valid = check_valid_number(card_number, even)
    return is_valid
    
    
def check_valid_number(number: str, even: bool) -> bool:
    number_list = [int(n) for n in number]
    
    numbers_sum = 0
    
    for i in range(len(number) - 2, -1, -2):
            
        doubled_number = number_list[i] * 2
            
        if (doubled_number >= 10):
                
            str_number = str(doubled_number)
            numbers_sum += sum([int(n) for n in str_number])
                
        else:
            numbers_sum += doubled_number

    for i in range(len(number) - 1, -1, -2):
        
        numbers_sum += number_list[i]
            
    return (numbers_sum % 10 == 0)
    
    
def is_visa(card_number: str) -> bool:

    return (card_number[0] == '4')


def is_amex(card_number: str) -> bool:
    
    valid_numbers = ['34', '37']
    
    return (card_number[:2] in valid_numbers)
    
    
def is_master(card_number: str) -> bool:
    
    valid_numbers = ['51', '52', '53', '54', '55']
    
    return (card_number[:2] in valid_numbers)
    
    
main()