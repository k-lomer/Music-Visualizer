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
    wave input{ 1.0f };
    wave expected_output{ 1.0f };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestSingle2) {
    wave input{ -1.0f };
    wave expected_output{ 1.0f };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestSingle3) {
    wave input{ 0.0f };
    wave expected_output{ 0.0f };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestSingle4) {
    wave input{ 0.1f };
    wave expected_output{ 0.1f };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestDouble) {
    wave input{ 1.0f, -1.0f };
    wave expected_output{ 0.0f, 2.0f };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestTrim) {
    wave input{ 1.0f, -1.0f, 0.0f };
    wave expected_output{ 0.0f, 2.0f };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestImpulse) {
    wave input{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    wave expected_output{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestSine) {
    wave input{ 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f };
    wave expected_output{ 0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestRandomValues) {
    wave input{ 1.0f, -1.0f, 0.4f, 0.8f, 1.2f, -0.3f, -0.7f, 0.9f };
    wave expected_output{ 2.3f, 0.82170414f, 3.90512484f, 1.68071482f, 1.5f, 1.68071482f, 3.90512484f, 0.82170414f };
    check_dft(input, expected_output);
}

TEST(TestFourierTransform, TestRandomValuesTrim) {
    wave input{ 1.0f, -1.0f, 0.4f, 0.8f, 1.2f, -0.3f, -0.7f, 0.9f, 0.0f, 0.1f, 0.2f };
    wave expected_output{ 2.3f, 0.82170414f, 3.90512484f, 1.68071482f, 1.5f, 1.68071482f, 3.90512484f, 0.82170414f };
    check_dft(input, expected_output);
}