#ifndef DOCX_V2_INNINGS_H
#define DOCX_V2_INNINGS_H

#include <string>

class Innings {
private:
    std::string batsman_;
    int overs_;
    int runs_;
    int legalBalls_;
    bool out_;

public:
    Innings(std::string batsman, int overs);

    void deliver(int pageNumber);
    bool isComplete() const;
    bool isOut() const;
    int runs() const;
    int legalBalls() const;
    std::string batsman() const;
};

#endif
