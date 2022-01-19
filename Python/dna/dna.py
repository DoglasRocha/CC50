import sys
from csv import DictReader
from sys import argv

def main():
    
    if (len(argv) != 3):
        print('Usage: python dna.py data.csv sequence.txt')
        sys.exit(1)
        
    database = read_database()
    sequence = read_sequence()

    strs = get_strs(database)
    
    
    
def read_database() -> list:
    
    results = []
    
    with open(argv[1]) as f:
        reader = DictReader(f)
        
        for row in reader:
            results.append(row)
            
    return results
    

def read_sequence() -> str:
    
    with open(argv[2]) as f:
        
        sequence = f.read()
        
    return sequence
    
    
def get_strs(database) -> list:
    
    strs = []
    
    for i in database[0].keys():
        strs.append(i) 
        
    strs = strs[1:]
    return strs
    
    
main()