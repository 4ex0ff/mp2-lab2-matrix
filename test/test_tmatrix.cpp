#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m1(2);
    for (int i = 0; i < m1.size(); ++i) {
        for (int j = 0; j < m1.size(); ++j) {
            m1[i][j] = i + 1;
        }
    }

    TDynamicMatrix<int> m2(m1);

    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(m1);

    EXPECT_NE(&m1[0][0], &m2[0][0]);
}

TEST(TDynamicMatrix, move_constructor_makes_source_empty)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(std::move(m1));

    EXPECT_EQ(0, m1.size());
    EXPECT_EQ(2, m2.size());
}

TEST(TDynamicMatrix, move_assignment_makes_source_empty)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(2);
    m2 = std::move(m1);

    EXPECT_EQ(0, m1.size());
    EXPECT_EQ(5, m2.size());
}

TEST(TDynamicMatrix, moved_matrix_keeps_source_data)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> exp(2);
    for (int i = 0; i < m1.size(); ++i) {
        for (int j = 0; j < m1.size(); ++j) {
            m1[i][j] = i + 1;
            exp[i][j] = i + 1;
        }
    }
    TDynamicMatrix<int> m2(std::move(m1));

    EXPECT_EQ(exp, m2);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(2);

    EXPECT_EQ(2, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(2);
    m[0][1] = 42;

    EXPECT_EQ(42, m[0][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(2);

    EXPECT_ANY_THROW(m.at(-1, 0));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(2);

    EXPECT_ANY_THROW(m.at(10, 0));
    EXPECT_ANY_THROW(m.at(0, 10));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(2);
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m.size(); ++j) {
            m[i][j] = i + 1;
        }
    }
    TDynamicMatrix<int> exp(m);
    m = m;

    EXPECT_EQ(exp, m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(2);
    for (int i = 0; i < m1.size(); ++i) {
        for (int j = 0; j < m1.size(); ++j) {
            m1[i][j] = i + 1;
        }
    }
    TDynamicMatrix<int> m2(2);
    m2 = m1;

    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(2);
    m2 = m1;

    EXPECT_EQ(5, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(3);
    for (int i = 0; i < m1.size(); ++i) {
        for (int j = 0; j < m1.size(); ++j) {
            m1[i][j] = i + 1;
        }
    }
    TDynamicMatrix<int> m2(2);
    m2 = m1;

    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(2);
    for (int i = 0; i < m1.size(); ++i) {
        for (int j = 0; j < m1.size(); ++j) {
            m1[i][j] = i + 1;
            m2[i][j] = i + 1;
        }
    }

    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(2);
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m.size(); ++j) {
            m[i][j] = i + 1;
        }
    }

    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(2);

    EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(2);
    for (int i = 0; i < m1.size(); ++i) {
        for (int j = 0; j < m1.size(); ++j) {
            m1[i][j] = 1;
            m2[i][j] = 1;
        }
    }

    TDynamicMatrix<int> exp(2);
    for (int i = 0; i < exp.size(); ++i) {
        for (int j = 0; j < exp.size(); ++j) {
            exp[i][j] = 2;
        }
    }

    EXPECT_EQ(exp, m1 + m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(2);

    EXPECT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(2);
    for (int i = 0; i < m1.size(); ++i) {
        for (int j = 0; j < m1.size(); ++j) {
            m1[i][j] = 3;
            m2[i][j] = 1;
        }
    }

    TDynamicMatrix<int> exp(2);
    for (int i = 0; i < exp.size(); ++i) {
        for (int j = 0; j < exp.size(); ++j) {
            exp[i][j] = 2;
        }
    }

    EXPECT_EQ(exp, m1 - m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(2);
        
    EXPECT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
    TDynamicMatrix<int> m(2);
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m.size(); ++j) {
            m[i][j] = 1;
        }
    }

    TDynamicMatrix<int> exp(2);
    for (int i = 0; i < exp.size(); ++i) {
        for (int j = 0; j < exp.size(); ++j) {
            exp[i][j] = 2;
        }
    }

    EXPECT_EQ(exp, m * 2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
    TDynamicMatrix<int> m(2);
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m.size(); ++j) {
            m[i][j] = 1;
        }
    }
    int arr[] = { 2, 2 };
    TDynamicVector<int> v(arr, 2);
    int expArr[] = { 4, 4 };
    TDynamicVector<int> exp(expArr, 2);

    EXPECT_EQ(exp, m * v);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_not_equal_size)
{
    TDynamicMatrix<int> m(2);
    TDynamicVector<int> v(5);

    EXPECT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;
    TDynamicMatrix<int> m2(2);
    m2[0][0] = 1;
    m2[0][1] = 2;
    m2[1][0] = 3;
    m2[1][1] = 4;

    TDynamicMatrix<int> mExp(2);
    mExp[0][0] = 7;
    mExp[0][1] = 10;
    mExp[1][0] = 15;
    mExp[1][1] = 22;

    EXPECT_EQ(mExp, m1 * m2);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(5);

    EXPECT_ANY_THROW(m1 * m2);
}

TEST(TDynamicMatrix, can_read_matrix)
{
    TDynamicMatrix<int> m(2);
    TDynamicMatrix<int> exp(2);
    for (int i = 0; i < exp.size(); ++i) {
        for (int j = 0; j < exp.size(); ++j) {
            exp[i][j] = i + 1;
        }
    }

    std::stringstream sstr;
    sstr << "1 1 " << "2 2\n";
    sstr >> m;

    EXPECT_EQ(exp, m);
}

TEST(TDynamicMatrix, can_write_matrix)
{
    TDynamicMatrix<int> m(2);
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m.size(); ++j) {
            m[i][j] = i + 1;
        }
    }

    std::string exp = "1 1 \n2 2 \n";
    std::stringstream sstr;
    sstr << m;

    EXPECT_EQ(exp, sstr.str());
}
