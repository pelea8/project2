#include "random.h"
#include "simulation.h"
#include "network.h"


void Network::resize(const size_t& size)
{
	values.clear();
	values.resize(size);
	RNG.normal(values,0,1);
}

bool Network::add_link(const size_t& a, const size_t& b)
{
	if (a < values.size() and b < values.size() and a!=b)
	{
		std::vector<size_t> comparisonVector(neighbors(a));
		
		for (auto v : comparisonVector)
		{
			if (v == b) return false;
		}
		links.emplace(a,b);
		links.emplace(b,a);
		return true;
	}
	return false;
}

size_t Network::random_connect(const double& degree_moyen)
{
	// Clear links
	links.clear();
	int taille(values.size());
	std:: vector<int> vector_index;
	
	for(int x(0); x < taille ; x++)
	{
		vector_index.push_back(x);
	}
	// For all nodes
	for (int a(0); a < taille ; a++)
	{
		size_t degree = RNG.poisson(degree_moyen);
		// Number of new links given by poisson distribution
		
		for (size_t b(0); b < degree; b++)
		{
			 
			bool link_true(false);
			while (!link_true)
			{
				RNG.uniform_int(vector_index, 0, taille);
				link_true = add_link(a,vector_index[b]);
			}		
		}
	}
	// Return number of links created
	return links.size()/2.0;
}

size_t Network::set_values(const std::vector<double>& newValues)
{
	if (values.size() < newValues.size())
	{
		values.clear();
		for (size_t a(0); a < values.size(); a++)
		{
			values[a] = newValues[a];
		}
		return values.size();
	}
	if (values.size() == newValues.size())
	{
		values.clear();
		for (size_t a(0); a <= values.size(); a++)
		{
			values[a] = newValues[a];
		}
		return values.size();
	}
	if (values.size() > newValues.size())
	{
		values.clear();
		for (size_t a(0); a < newValues.size(); a++)
		{
			values[a] = newValues[a];
		}
		return newValues.size();
	}
	return 1;
}

size_t Network::size() const
{
	return values.size();
}

size_t Network::degree(const size_t &_n) const
{
	return links.count(_n);
}

double Network::value(const size_t &_n) const
{
	return values[_n];
}

std::vector<double> Network::sorted_values() const
{
	std::vector<double> sorted = values;

	// Sort in descending order using a lambda expression
	std::sort(sorted.begin(), sorted.end());
	std::reverse(sorted.begin(), sorted.end()); 

	return sorted;
}

std::vector<size_t> Network::neighbors(const size_t& a) const
{
	std::vector<size_t> neighbours;

	// equal_range returns a std::pair of iterators 
	auto range = links.equal_range(a);

	
	for (auto b = range.first; b != range.second; b++)
		neighbours.push_back(b->second);

	return neighbours;
}
