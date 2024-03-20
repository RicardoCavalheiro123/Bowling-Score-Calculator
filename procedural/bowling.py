def read_rolls_from_file(filename):
    with open(filename, 'r') as file:
        rolls = [int(roll) for line in file for roll in line.split()]
   
    return rolls


def calculate_score(rolls):
    total_score = 0
    roll_index = 0 # Round number

    for frame in range(10):
        total_score += frame_score(rolls[roll_index])
        if (roll_index == 9): 
            print("Frame", roll_index, "Score:", total_score)
            break
        if is_strike(rolls, roll_index):
            if(is_strike(rolls, roll_index + 1)):
                total_score += rolls[roll_index + 1][0] + rolls[roll_index + 2][0]
            else:
                total_score += rolls[roll_index + 1][0] + rolls[roll_index + 1][1]
            
        elif is_spare(rolls, roll_index):
            total_score += rolls[roll_index + 1][0]
        print("Frame", roll_index, "Score:", total_score)
        roll_index += 1
    return total_score


def is_strike(rolls, roll_index):
    return rolls[roll_index][0] == 10 and roll_index != 9


def is_spare(rolls, roll_index):
    return sum(rolls[roll_index]) == 10 and roll_index != 9


def frame_score(rolls):
    return sum(rolls)



def frame_separator(rolls):
    frames = []
    round = 0
    i = 0
    while round < 10:
  
        if round == 9:
            frames.append(rolls[i:])
            break
        if rolls[i] == 10:
            frames.append([rolls[i]])
        else:
            frames.append(rolls[i:i+2])
            i += 1
        i += 1
        round += 1
      
    return frames

def main():
    import sys
    if len(sys.argv) != 2:
        print("Usage: python bowling.py <input_file>")
        sys.exit(1)

    filename = sys.argv[1]
   
    rolls = read_rolls_from_file(filename)
    frames = frame_separator(rolls)
    total_score = calculate_score(frames)

    print("Total Score:", total_score)


if __name__ == "__main__":
    main()
