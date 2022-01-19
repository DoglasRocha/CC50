# reads a dna sequence and identifies who is the owner of the dna

# import modules that are necessary to the program
import sys
import re
from csv import DictReader
from sys import argv


def main():
    
    # if the program has the wrong number of args, exit and print the correct usage
    if (len(argv) != 3):
        print('Usage: python dna.py data.csv sequence.txt')
        sys.exit(1)
        
    # reads the database and the sequence to be analyzed
    database = read_database()
    sequence = read_sequence()

    # gets the strs and the repeats
    strs = get_strs(database)
    repeats = find_repeats(sequence, strs)
    
    # finds the person who the dna belongs and prints the name of the person
    person = find_person(database, repeats)
    print(person)
    
    
# reads the database and return a dict with it
def read_database() -> list:
    
    results = []
    
    with open(argv[1]) as f:
        reader = DictReader(f)
        
        for row in reader:
            results.append(row)
            
    return results
    

# reads the sequence to be analyzed and return a string with it
def read_sequence() -> str:
    
    with open(argv[2]) as f:
        sequence = f.read()
        
    return sequence
    
    
# gets the strs from the database
def get_strs(database: dict) -> list:
    
    strs = []
    
    for i in database[0].keys():
        strs.append(i) 
        
    strs = strs[1:]
    return strs
    
    
# using regex, finds the bigger sequence of each str
def find_repeats(sequence: str, strs: str) -> dict:
    
    results = dict()
    for dna_sequence in strs:
        
        for i in range(1, 51):
            match = re.search(dna_sequence * i, sequence)
            
            if (match):
                results[dna_sequence] = str(i)
               
    return results


# finds who the dna belongs. if does not found anyone, return 'No match'
def find_person(database: list, repeats: dict) -> str:
    
    for person in database:
        
        sequences = person.items() 
        sequences = dict(sequences)
        sequences.pop('name')
        
        if (sequences == repeats):
            return person['name']    
        
    return 'No match'
    
    
main()