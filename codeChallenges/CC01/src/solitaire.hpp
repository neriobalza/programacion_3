// Coloca aquí tu nombre y tu cédula.

Color card_color(const Card &c)
{
    if (std::get<0>(c) == Suit::Clubs || std::get<0>(c) == Suit::Spades)
    {
        return Color::Black;
    }
    return Color::Red;
}

card_value_t card_value(const Card &c)
{
    if (std::get<1>(c) == Rank::Ace)
    {
        return 11;
    }
    else if (std::get<1>(c) == Rank::King || std::get<1>(c) == Rank::Queen || std::get<1>(c) == Rank::Jack)
    {
        return 10;
    }
    return (int)std::get<1>(c) + 1;
}

std::list<Card> remove_card(const std::list<Card> &cs, const Card &c)
{
    for (auto card : cs)
    {
        if (card == c)
        {
            std::list<Card> cop;
            std::copy_if(cs.begin(), cs.end(), std::back_inserter(cop), [c](Card item)
                         { return item != c; });
            return cop;
        }
    }

    throw CardExcept::IllegalMovement;
}

bool all_same_color(const std::list<Card> &cs)
{
    Color baseColor = card_color(cs.front());

    for (auto item : cs)
    {
        if (card_color(item) != baseColor)
            return false;
    }
    return true;
}

card_value_t sum_cards(const std::list<Card> &cs)
{
    return std::accumulate(cs.begin(), cs.end(), 0, [](int acc, Card item)
                           { return acc + card_value(item); });
}

card_value_t score(const std::list<Card> &cs, card_value_t goal)
{
    int sum = sum_cards(cs);
    int preliminar = (sum > goal) ? 3 * (sum - goal) : goal - sum;

    if (all_same_color(cs))
    {
        return preliminar / 2;
    }

    return preliminar;
}

card_value_t officiate(std::list<Card> cs, std::list<MovementPtr> ms, card_value_t goal)
{
    std::list<Card> hs;

    return 0;
}