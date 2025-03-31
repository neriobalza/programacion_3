#pragma once

enum class Suit
{
    Spades,
    Clubs,
    Hearts,
    Diamonds
};

enum class Rank
{
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

enum class Color
{
    NonColor,
    Red,
    Black
};

enum class CardExcept
{
    IllegalMovement
};

using Card = std::tuple<Suit, Rank>;
using card_value_t = unsigned int;

// Interface to represent any movement in the game.
class Movement
{
public:
    virtual ~Movement() {}

    virtual bool has_card() const noexcept = 0;

    virtual const Card& get_card() const = 0;

    virtual bool operator == (const Movement &) const noexcept = 0;
};

class Draw : public Movement
{
public:
    bool has_card() const noexcept override
    {
        return false;
    }

    const Card& get_card() const override
    {
        throw std::logic_error("Movement draw has not an associated card");
    }

    bool operator == (const Movement&) const noexcept override
    {
        // Two draw moves are always equal.
        return true;
    }
};

class Discard : public Movement
{
public:
    Discard(const Card &_card) : card{_card} { /* empty */ }

    bool has_card() const noexcept override
    {
        return true;
    }

    const Card& get_card() const override
    {
        return card;
    }

    bool operator == (const Movement& movement) const noexcept override
    {
        return card == dynamic_cast<const Discard&>(movement).card;
    }

private:
    Card card;
};

using MovementPtr = std::shared_ptr<Movement>;

MovementPtr make_draw()
{
    return std::make_shared<Draw>();
}

MovementPtr make_discard(const Card& card)
{
    return std::make_shared<Discard>(card);
}

std::ostream& operator << (std::ostream& out, const Color& color) noexcept
{
    switch (color)
    {
    case Color::NonColor:
        out << "Non-color";
        break;
    case Color::Red:
        out << "Red";
        break;
    case Color::Black:
        out << "Black";
        break;
    }

    return out;
}

std::ostream& operator << (std::ostream& out, const Suit& suit) noexcept
{
    switch (suit)
    {
    case Suit::Spades:
        out << "Spades";
        break;
    case Suit::Diamonds:
        out << "Diamonds";
        break;
    case Suit::Clubs:
        out << "Clubs";
        break;
    case Suit::Hearts:
        out << "Hearts";
    }

    return out;
}

std::ostream& operator << (std::ostream& out, const Rank& rank) noexcept
{
    switch (rank)
    {
    case Rank::Ace:
        out << "Ace";
        break;
    case Rank::Jack:
        out << "Jack";
        break;
    case Rank::Queen:
        out << "Queen";
        break;
    case Rank::King:
        out << "King";
        break;
    default:
        out << static_cast<card_value_t>(rank);
    }

    return out;
}

std::ostream& operator << (std::ostream& out, const Card& card) noexcept
{
    out << "(" << std::get<0>(card) << ", " << std::get<1>(card) << ")";
    return out;
}

std::ostream& operator << (std::ostream& out, MovementPtr m) noexcept
{
    if (m->has_card())
    {
        out << "Discard " << m->get_card();
    }
    else
    {
        out << "Draw";
    }

    return out;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const std::list<T>& l) noexcept
{
    out << "[";

    auto it = l.begin();

    if (it != l.end())
    {
        out << *it;
        ++it;
    }

    while (it != l.end())
    {
        out << ", " << *it;
        ++it;
    }

    out << "]";

    return out;
}