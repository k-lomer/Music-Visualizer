#include "gtest/gtest.h"

#include "../Utilities/dsp_utilities.h"

// Values based on https://scistatcalc.blogspot.com/2013/12/fft-calculator.html and python scipy.fft

void check_dft(const wave& input, const wave& expected_output) {
    wave output = dft(input);
    EXPECT_EQ(expected_output.size(), output.size());
    for (int i = 0; i < expected_output.size(); ++i)
    {
        EXPECT_FLOAT_EQ(expected_output[i], output[i]);
    }
}

TEST(TestFourierTransform, TestSingle1) {
    wave input{ 1.0 };
    wave expected_output{ 1.0 };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestSingle2) {
    wave input{ -1.0 };
    wave expected_output{ 1.0 };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestSingle3) {
    wave input{ 0.0 };
    wave expected_output{ 0.0 };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestSingle4) {
    wave input{ 0.1 };
    wave expected_output{ 0.1 };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestDouble) {
    wave input{ 1.0, -1.0 };
    wave expected_output{ 0.0, 2.0 };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestTrim) {
    wave input{ 1.0, -1.0, 0.0 };
    wave expected_output{ 0.0, 2.0 };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestImpulse) {
    wave input{ 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    wave expected_output{ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestSine) {
    wave input{ 1.0, 0.0, -1.0, 0.0, 1.0, 0.0, -1.0, 0.0 };
    wave expected_output{ 0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 4.0, 0.0 };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestRandomValues) {
    wave input{ 1.0, -1.0, 0.4, 0.8, 1.2, -0.3, -0.7, 0.9 };
    wave expected_output{ 2.3, 0.82170414, 3.90512484, 1.68071482, 1.5, 1.68071482, 3.90512484, 0.82170414 };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestRandomValuesTrim) {
    wave input{ 1.0, -1.0, 0.4, 0.8, 1.2, -0.3, -0.7, 0.9, 0.0, 0.1, 0.2 };
    wave expected_output{ 2.3, 0.82170414, 3.90512484, 1.68071482, 1.5, 1.68071482, 3.90512484, 0.82170414 };
    check_dft(input, expected_output);
}