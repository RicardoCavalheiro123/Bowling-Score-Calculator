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



if __name__ == "__main__":
    import sys

    # Read frames from standard input
    frames = [eval(line) for line in sys.stdin]


    print("Frames:", frames)
    total_score = calculate_score(frames)
    print("Total Score:", total_score)