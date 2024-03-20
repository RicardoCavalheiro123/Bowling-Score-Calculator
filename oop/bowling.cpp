#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class Frame {
protected:
    std::vector<int> rolls;


public:
    Frame(const std::vector<int>& _rolls) : rolls(_rolls) {}

    virtual int score() const = 0;

    virtual bool isStrike() const = 0;

    virtual bool isSpare() const = 0;

    virtual void printFrame() const = 0;

    virtual bool isFinalFrame() const = 0;

    std::vector<int> getRolls() const {
        return rolls;
    }
};

class NormalFrame : public Frame {
public:
    NormalFrame(const std::vector<int>& _rolls) : Frame(_rolls) {}

    int score() const override {
        int frameScore = 0;
        for (int roll : rolls) {
            frameScore += roll;
        }
        return frameScore;
    }

    bool isStrike() const override {
        return rolls[0] == 10;
    }

    bool isSpare() const override {
        return rolls[0] + rolls[1] == 10 && !isStrike();
    }

    void printFrame() const override {
        for (int i = 0; i < rolls.size(); ++i) {
            std::cout << rolls[i] << " ";
        }
        std::cout << std::endl;
    }
    bool isFinalFrame() const {
        return false;
    }
};

class FinalFrame : public Frame {
public:
    FinalFrame(const std::vector<int>& _rolls) : Frame(_rolls) {}

    std::vector<int> getRolls() const {
        return rolls;
    }
    int score() const override {
        int frameScore = 0;
        for (int roll : rolls) {
            frameScore += roll;
        }
        return frameScore;
    }

    bool isStrike() const override {
        return false;
    }

    bool isSpare() const override {
        return rolls.size() >= 2 && rolls[0] + rolls[1] == 10 && !isStrike();
    }

    void printFrame() const override {
        for (int i = 0; i < rolls.size(); ++i) {
            std::cout << rolls[i] << " ";
        }
        std::cout << std::endl;
    }

    bool isFinalFrame() const {
        return true;
    }
};

class BowlingGame {
private:
    std::vector<Frame*> frames;

public:
    BowlingGame(const std::vector<int>& rolls) {
        int round = 0;
        for (int i = 0; i < rolls.size(); i++) {
            if(round == 9){
                std::vector<int> finalRolls;

                for(int j = i; j < rolls.size(); j++){

                    finalRolls.push_back(rolls[j]);
                }
                frames.push_back(new FinalFrame(finalRolls));
                break;
            }
            else{
                if(rolls[i] == 10){
                    frames.push_back(new NormalFrame({rolls[i]}));
                } else {
                    frames.push_back(new NormalFrame({rolls[i], rolls[i+1]}));
                    i++;
                }
            }
            round++;
        }
    }

    ~BowlingGame() {
        for (Frame* frame : frames) {
            delete frame;
        }
    }

    int calculateScore() const {
        int totalScore = 0;
        
        for(int i = 0; i < frames.size(); i++){
            totalScore += frames[i]->score();
            if(frames[i]->isFinalFrame()) break;
            if(frames[i]->isStrike()){
                if(frames[i+1]->isStrike()){
                    totalScore += frames[i+1]->getRolls()[0] + frames[i+2]->getRolls()[0];
                }
                else{
                    totalScore += frames[i+1]->getRolls()[0] + frames[i+1]->getRolls()[1];
                }
            }
            else if(frames[i]->isSpare()){
                totalScore += frames[i+1]->getRolls()[0];
            }
            std::cout << "Frame " << i+1 << " Score: " << totalScore << std::endl;
        }
        return totalScore;
    }

    void printFrames() const {
        for (Frame* frame : frames) {
            frame->printFrame();
        }
    }
};

std::vector<int> readRollsFromFile(const std::string& filename) {
    std::vector<int> rolls;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return rolls;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int roll;
        while (ss >> roll) {
            rolls.push_back(roll);
        }
    }

    return rolls;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<int> rolls = readRollsFromFile(filename);

    BowlingGame game(rolls);

    std::cout << "Total Score: " << game.calculateScore() << std::endl;

    return 0;
}
