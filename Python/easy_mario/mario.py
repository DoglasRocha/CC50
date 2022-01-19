# gets a height from the user and makes a mario pyramid of the given height
def main():
    height = get_height()

    for i in range(1, height + 1):
        # calcs the amount of spaces needed
        spaces = height - i
        
        # prints the spaces
        for j in range(spaces):
            print(' ', end='')
            
        # prints the hashes
        for k in range(i):
            print('#', end='')
            
        # new line
        print()


# gets the height from the user, refusing everything except values
# between 0 and 9
def get_height():
    str_height = input('Height: ')
    
    if (str_height.isdecimal()):
        height = int(str_height)
        
        if (9 > height > 0):
            return height

    return get_height()


main()