#include <bitset>
#include <iostream>
#include <string>
#include <vector>

// 17.10/17.11/17.12/17.13: quiz results as bitsets. The 17.11 Quiz class
// holds eleven answers, updates them with update_answer, counts the
// correct ones and prints the score like 17.13.

class Quiz
{
public:
    explicit Quiz(const std::bitset<11> &solution) : answers(solution)
    {
    }

    void update_answer(std::size_t question, bool correct)
    {
        answers.set(question, correct);
    }

    std::size_t correct_count() const
    {
        return answers.count();
    }

    void print_score() const
    {
        std::cout << "score: " << correct_count() << "/11 ("
                  << answers.to_string() << ")\n";
    }

private:
    std::bitset<11> answers;
};

int main()
{
    const std::vector<int> marks{1, 2, 3, 5, 8, 13};
    std::bitset<32> flags;
    for (const int position : marks)
    {
        flags.set(position);
    }
    std::cout << "17.10 flags: " << flags.to_string() << " ("
              << flags.count() << " set)\n";

    const std::bitset<11> solution(std::string("10101010101"));
    Quiz quiz(solution);
    quiz.update_answer(1, true);
    quiz.update_answer(2, true);
    quiz.update_answer(5, true);
    quiz.print_score();
    return 0;
}
