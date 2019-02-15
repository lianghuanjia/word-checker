// WordChecker.cpp
//
// ICS 46 Spring 2018
// Project #4: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>

WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{   
    std::vector<std::string> SwapVec = SwapAdjacent(word);
    std::vector<std::string> holder1 = InsertAdjacent(word);
    SwapVec.insert(SwapVec.end(), holder1.begin(), holder1.end());
    std::vector<std::string> holder2 = DeleteCharacter(word);
    SwapVec.insert(SwapVec.end(), holder2.begin(), holder2.end());
    std::vector<std::string> holder3 = ReplaceCharacter(word);
    SwapVec.insert(SwapVec.end(), holder3.begin(), holder3.end());
    std::vector<std::string> holder4 = SplitIntoTwo(word);
    SwapVec.insert(SwapVec.end(), holder4.begin(), holder4.end());
    std::vector<std::string>::iterator ip;

    ip = std::unique(SwapVec.begin(), SwapVec.end());
    SwapVec.resize(std::distance(SwapVec.begin(), ip));

    return SwapVec;
}


std::vector<std::string> WordChecker::SwapAdjacent(const std::string& word) const
{
    // Note: the word could have content or it's an empty string
    std::vector<std::string> return_vector;
    int word_size = word.size();
    if (word_size == 0)
        {
        return return_vector;
        }
    else if (word_size == 1)
        {
        if (wordExists(word) == true)
            return_vector.push_back(word);
        return return_vector;
        }
    else
        {
        for ( int  i = 0; i < (word_size - 1); ++i )
            {
            std::string new_word = word;
            new_word[i] = word[i+1]; 
            new_word[i+1] = word[i];
            if (wordExists(new_word) == true)
                {
                return_vector.push_back(new_word);
                }
            }
        return return_vector;
        }
}

std::vector<std::string> WordChecker::InsertAdjacent(const std::string& word) const
{
    // Note: the word could have content or it's an empty string
    std::string Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<std::string> return_vector;
    std::string add_string;
    int word_size = word.size();
    if (word_size == 0)
        return return_vector;
    else if (word_size == 1)   // If the word is one character, should you also insert them in the beginning and the end of the character??
        {
        if (wordExists(word) == true)
            {
            return_vector.push_back(word);
            }
        return return_vector;
        }
    else
        {
        for (int i = 0; i <= word_size; ++i)
            {
            int Alphabet_size = Alphabet.size();
            for (int j = 0; j < Alphabet_size; ++j)
                {
                std::string new_word = word;
                add_string = Alphabet[j];
                new_word.insert(i, add_string);/////////////////
                if (wordExists(new_word) == true)
                    {
                    return_vector.push_back(new_word);                
                    }
                }
            }
        return return_vector;
        }   
}

std::vector<std::string> WordChecker::DeleteCharacter(const std::string& word) const
{
    // Note: the word could have content or it's an empty string
    std::vector<std::string> return_vector;
    int word_size = word.size();
    if (word_size == 0)
        return return_vector;
    // if the word only has one character, do we check it in the dictionary or delete it?
    else
        {   
        for (int i = 0 ; i < word_size; ++i)
            {
            std::string new_word = word;
            new_word.erase(i,1);
            if (wordExists(new_word) == true)
                {
                return_vector.push_back(new_word);
                }
            }
        return return_vector;
        }
}


std::vector<std::string> WordChecker::ReplaceCharacter(const std::string& word) const
{
    std::string Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<std::string> return_vector;
    int word_size = word.size();
    if (word_size == 0)
        return return_vector;
    else
        {
        for (int i = 0; i < word_size; ++i)
            {
            int alphabet_size = Alphabet.size();
            for (int j = 0; j < alphabet_size; ++j)
                {
                std::string new_word = word;
                new_word[i] = Alphabet[j];
                if (wordExists(new_word) == true)
                    {
                    return_vector.push_back(new_word);
                    }

                }
            }
        return return_vector;
        }
}


std::vector<std::string> WordChecker::SplitIntoTwo(const std::string& word) const
{
    using namespace boost::algorithm; 
    std::vector<std::string> return_vector;
    int word_size = word.size();
    if (word_size == 0)
        return return_vector;
    else if (word_size == 1)
        {
        if (wordExists(word) == true)
            {
            return_vector.push_back(word);
            }
        return return_vector;
        }
    else
        {
        for (int i = 0; i < (word_size-1); ++i)
            {
                std::vector<std::string> holder;
                std::string new_word = word;
                new_word.insert(i+1, " ");
                split(holder, new_word, is_any_of(" "));
                if (wordExists(holder[0]) == true && wordExists(holder[1])==true)
                    {
                    int first_size  = holder[0].size();
                    holder[0].insert(first_size, " ");
                    int second_size = holder[0].size();
                    holder[0].insert(second_size, holder[1]);
                    return_vector.push_back(holder[0]);
                    }
            }
        }
        return return_vector;
}









