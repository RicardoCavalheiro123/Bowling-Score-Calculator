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

if __name__ == "__main__":
    import sys

    # Read frames from standard input
    rolls = [eval(line) for line in sys.stdin]

    frames = frame_separator(rolls)
   
    for frame in frames:
        print(frame)

