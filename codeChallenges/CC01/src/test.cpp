#include <bits/stdc++.h>

#include <defs.hpp>
#include <solitaire.hpp>

template <typename T, typename Cmp = std::equal_to<T>>
bool list_equal(const std::list<T> &l1, const std::list<T> &l2, Cmp &&cmp = Cmp{}) noexcept
{
    if (l1.size() != l2.size())
    {
        return false;
    }

    auto it1 = l1.begin();

    for (auto it2 = l2.begin(); it2 != l2.end(); ++it2, ++it1)
    {
        if (!cmp(*it1, *it2))
        {
            return false;
        }
    }

    return true;
}

bool operator==(MovementPtr m1, MovementPtr m2) noexcept
{
    return *m1 == *m2;
}

template <typename T>
bool operator==(const std::list<T> &l1, const std::list<T> &l2) noexcept
{
    return list_equal(l1, l2);
}

template <typename T>
void assert_equal(const T &current, const T &expected) noexcept
{
    if (current != expected)
    {
        std::cerr << "Failed!\n";
        std::cerr << "Current: " << current << "\n";
        std::cerr << "Expected: " << expected << "\n";
        abort();
    }

    std::cout << "Ok!\n";
}

int main()
{
    std::cout << "Testing card_color\n";
    assert_equal(card_color(Card{Suit::Spades, Rank::Jack}), Color::Black);

    std::cout << "Testing card_value\n";
    assert_equal<card_value_t>(card_value(Card{Suit::Spades, Rank::Ace}), 11U);
    // std::cout << "Testing card_value\n";
    // assert_equal<card_value_t>(card_value(Card{Suit::Spades, Rank::Five}), 5U);

    std::cout << "Testing remove_card\n";
    assert_equal(remove_card({Card{Suit::Hearts, Rank::King}}, Card{Suit::Hearts, Rank::King}), std::list<Card>{});

    // std::cout << "Testing remove_card\n";
    // assert_equal(remove_card({Card{Suit::Hearts, Rank::King}}, Card{Suit::Hearts, Rank::Ace}), std::list<Card>{Card{Suit::Hearts, Rank::King}});

    std::cout << "Testing all_same_color\n";
    assert_equal(all_same_color({Card{Suit::Spades, Rank::Three}}), true);

    std::cout << "Testing sum_cards\n";
    assert_equal<card_value_t>(sum_cards({Card{Suit::Spades, Rank::Three}}), 3U);

    std::cout << "Testing score\n";
    assert_equal<card_value_t>(score({Card{Suit::Hearts, Rank::Two}, Card{Suit::Clubs, Rank::Four}}, 10), 4U);

    std::cout << "Testing officiate 1\n";
    assert_equal<card_value_t>(officiate({Card{Suit::Hearts, Rank::Two}, Card{Suit::Clubs, Rank::Four}}, {make_draw()}, 15), 6U);

    std::list<Card> cs1{
        {Card{Suit::Clubs, Rank::Ace}, Card{Suit::Spades, Rank::Ace}, Card{Suit::Clubs, Rank::Ace}, Card{Suit::Spades, Rank::Ace}}};

    std::list<MovementPtr> ms{
        {make_draw(), make_draw(), make_draw(), make_draw(), make_draw()}};

    std::cout << "Testing officiate 2\n";
    assert_equal(officiate(cs1, ms, 42), 3U);

    std::list<Card> cs2{
        {Card{Suit::Clubs, Rank::Ace}, Card{Suit::Spades, Rank::Ace}, Card{Suit::Clubs, Rank::Ace}, Card{Suit::Spades, Rank::Ace}}};

    std::list<MovementPtr> expected_ms{
        {make_draw(), make_draw(), make_draw(), make_discard(Card{Suit::Clubs, Rank::Ace}), make_draw(), make_draw()}};

    return 0;
}
