

def read_rolls_from_file(filename):
    with open(filename, 'r') as file:
        rolls = [int(roll) for line in file for roll in line.split()]
   
    return rolls

if __name__ == "__main__":
    import sys

    # Read rolls from file
    filename = sys.argv[1]
    rolls = read_rolls_from_file(filename)

    for roll in rolls:
        print(roll)

    

