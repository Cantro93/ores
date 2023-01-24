#pragma once
#ifndef _ORE_
#define _ORE_
using namespace std;
#include <random>
#include <vector>
#include <ctime>
#include <functional>
template<typename type>
type std_rand(vector<type> pool)
{
	return pool[rand() % (pool.size() - 1)];
}
template<typename type>
class ore
{
public:
	ore(vector<type> data = vector<type>()) : content(data) { content.reserve(1); }
	~ore()
	{
		content.clear();
		content.~vector<type>();
	}
	int add(type element)
	{
		content.push_back(element);
		return content.size() - 1;
	}
	type remove(int position)
	{
		//counter
		int i = 0;
		//create new temporary vector
		vector<type> temporary;
		temporary.reserve(content.size() - 1);
		//create an T temporary element
		type element;
		//it will store removed element to return it as output
		element = content[position];
		//copy all the content to temporary vector except element to remove
		//maybe this method is longer, but author knows how it works and he thinks that it should work
		for (type var : content)
		{
			//copy every element except that to remove
			if (!(i == position))
			{
				temporary[i] = var;
			};
			i++;
		}

		//clear the content to remove that element
		content.clear();

		//now there should be no elements to remove

		//recreate the vector with content
		content.reserve(temporary.size());
		//now copy all the other elements back to the content vector
		content = temporary;
		//now the temporary vector will be removed to make sure that function will not leave anything to clear
		temporary.clear();

		//do the same with other things
		i = NULL;

		//now return the removed element
		return element;
	}
	type random()
	{
		return r(content);
	}
	//an alias to 'add'
	ore& operator<<(type b)
	{
		add(b);
		return *this;
	}
	//an alias to 'random'
	type operator()()
	{
		return random();
	}
	//overloaded randomizing
	vector<type> operator()(int amount)
	{
		vector<type> tmp;
		tmp.reserve(1);
		for (int i = 0; i < amount; i++)
		{
			tmp.push_back(random());
		}
		return tmp;
	}
	template<typename container>
	class smelter
	{
	public:
		//smelter without any ore will not be useful, pushing method is also required
		smelter(ore* target, void push_fc(container& cont, type data)) : input(target), amount(1), is_tmp(false) { push_method = push_fc; }
		//set amount
		smelter& operator()(int quantity, bool tmp = false)
		{
			amount = quantity;
			is_tmp = tmp;
			return *this;
		}
		//call randomizing
		smelter& operator>>(container& target)
		{
			vector<type> tmp = input->operator()(amount);
			for (type d : tmp)
			{
				push_method(target, d);
			}
			if (is_tmp)
			{
				is_tmp = false;
				amount = 1;
			}
			return *this;
		}
		//set pushing method
		smelter& set_pusher(void push_fc(container& cont, type data))
		{
			push_method = push_fc;
			return *this;
		}
	private:
		//source
		ore* input;
		bool is_tmp;
		//required amount
		int amount;
		//pusher, pushing method
		function<void(container&, type)> push_method;
	};
	//RANDOMIZER - contains a randomization algorithm called by an ore
	class randomizer
	{
	public:
		//algorithm is required
		randomizer(type f(vector<type> pool) = std_rand) { fc = f; }
		//set algorithm
		randomizer& set_fc(type f(vector<type> pool) = std_rand) { fc = f; }
		//call algorithm
		type randomize(vector<type> pool)
		{
			return fc(pool);
		}
		//same as 'randomize'
		type operator()(vector<type> pool)
		{
			return fc(pool);
		}
	private:
		//algorithm
		function<type(vector<type>)> fc;
	};
	ore& set_randomizer(randomizer nr)
	{
		r = nr;
	}
	ore& set_randomizer(type rf(vector<type> pool))
	{
		r.set_fc(rf);
	}
	ore* operator&()
	{
		return this;
	}
private:
	typename vector<type> content;
	//randomizer
	randomizer r;
};
#endif // !_ORE_
