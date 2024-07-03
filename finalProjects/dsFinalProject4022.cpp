#include <iostream>
#include <vector>
#include <cmath>

struct Term {
    double coefficient;
    int exponent;
};

class Polynomial {
public:
    // Create Polynomial
    Polynomial() {}

    // Add Term
    void addTerm(double coefficient, int exponent) {
        terms.push_back({coefficient, exponent});
    }

    // Evaluate Polynomial
    double evaluatePolynomial(double x) {
        double result = 0.0;
        for (const auto& term : terms) {
            result += term.coefficient * pow(x, term.exponent);
        }
        return result;
    }

    // Add Polynomials
    Polynomial addPolynomials(const Polynomial& other) {
        Polynomial result;
        size_t i = 0, j = 0;
        while (i < terms.size() || j < other.terms.size()) {
            if (i < terms.size() && (j >= other.terms.size() || terms[i].exponent > other.terms[j].exponent)) {
                result.addTerm(terms[i].coefficient, terms[i].exponent);
                i++;
            } else if (j < other.terms.size() && (i >= terms.size() || other.terms[j].exponent > terms[i].exponent)) {
                result.addTerm(other.terms[j].coefficient, other.terms[j].exponent);
                j++;
            } else {
                double newCoefficient = terms[i].coefficient + other.terms[j].coefficient;
                if (newCoefficient != 0.0) {
                    result.addTerm(newCoefficient, terms[i].exponent);
                }
                i++;
                j++;
            }
        }
        return result;
    }

    // Subtract Polynomials
    Polynomial subtractPolynomials(const Polynomial& other) {
        Polynomial result;
        size_t i = 0, j = 0;
        while (i < terms.size() || j < other.terms.size()) {
            if (i < terms.size() && (j >= other.terms.size() || terms[i].exponent > other.terms[j].exponent)) {
                result.addTerm(terms[i].coefficient, terms[i].exponent);
                i++;
            } else if (j < other.terms.size() && (i >= terms.size() || other.terms[j].exponent > terms[i].exponent)) {
                result.addTerm(-other.terms[j].coefficient, other.terms[j].exponent);
                j++;
            } else {
                double newCoefficient = terms[i].coefficient - other.terms[j].coefficient;
                if (newCoefficient != 0.0) {
                    result.addTerm(newCoefficient, terms[i].exponent);
                }
                i++;
                j++;
            }
        }
        return result;
    }

    // Multiply Polynomials
    Polynomial multiplyPolynomials(const Polynomial& other) {
        Polynomial result;
        for (const auto& term1 : terms) {
            for (const auto& term2 : other.terms) {
                result.addTerm(term1.coefficient * term2.coefficient, term1.exponent + term2.exponent);
            }
        }
        return result;
    }

    // Derivative of Polynomial
    Polynomial derivativeOfPolynomial() {
        Polynomial result;
        for (const auto& term : terms) {
            if (term.exponent > 0) {
                result.addTerm(term.coefficient * term.exponent, term.exponent - 1);
            }
        }
        return result;
    }

        // Integral of Polynomial (continued)
    Polynomial integralOfPolynomial() {
        Polynomial result;
        for (const auto& term : terms) {
            result.addTerm(term.coefficient / (term.exponent + 1), term.exponent + 1);
        }
        return result;
    }

    // Print Polynomial
    void printPolynomial() {
        bool firstTerm = true;
        for (const auto& term : terms) {
            if (!firstTerm) {
                if (term.coefficient > 0) {
                    std::cout << " + ";
                } else {
                    std::cout << " - ";
                }

}
            firstTerm = false;
            std::cout << std::abs(term.coefficient);
            if (term.exponent > 0) {
                std::cout << "x^" << term.exponent;
            }
        }
        if (terms.empty()) {
            std::cout << "0";
        }
        std::cout << std::endl;
    }

private:
    std::vector<Term> terms;
};

int main() {
    Polynomial p1, p2;

    // Create Polynomial 1: 3x^4 + 2x^2 - 5
    p1.addTerm(3, 4);
    p1.addTerm(2, 2);
    p1.addTerm(-5, 0);

    // Create Polynomial 2: 2x^3 - x + 4
    p2.addTerm(2, 3);
    p2.addTerm(-1, 1);
    p2.addTerm(4, 0);

    // Print Polynomials
    std::cout << "Polynomial 1: ";
    p1.printPolynomial();
    std::cout << "Polynomial 2: ";
    p2.printPolynomial();

    // Evaluate Polynomials
    std::cout << "Evaluating Polynomial 1 at x = 2: " << p1.evaluatePolynomial(2) << std::endl;
    std::cout << "Evaluating Polynomial 2 at x = 2: " << p2.evaluatePolynomial(2) << std::endl;

    // Add Polynomials
    Polynomial p3 = p1.addPolynomials(p2);
    std::cout << "Polynomial 1 + Polynomial 2: ";
    p3.printPolynomial();

    // Subtract Polynomials
    Polynomial p4 = p1.subtractPolynomials(p2);
    std::cout << "Polynomial 1 - Polynomial 2: ";
    p4.printPolynomial();

    // Multiply Polynomials
    Polynomial p5 = p1.multiplyPolynomials(p2);
    std::cout << "Polynomial 1 * Polynomial 2: ";
    p5.printPolynomial();

    // Derivative of Polynomial
    Polynomial p6 = p1.derivativeOfPolynomial();
    std::cout << "Derivative of Polynomial 1: ";
    p6.printPolynomial();

    // Integral of Polynomial
    Polynomial p7 = p1.integralOfPolynomial();
    std::cout << "Integral of Polynomial 1: ";
    p7.printPolynomial();

    return 0;
}