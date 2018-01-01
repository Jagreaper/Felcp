#pragma once

#include <vector>
#include <iterator>

namespace Jagerts::Felcp::Helpers
{
	class VectorHelper sealed
	{
	public:
		template<class T>
		static inline bool Contains(const std::vector<T>& vector, const T& item)
		{
			for (int index = 0; index < vector.size(); index++)
			{
				if (item == vector[index])
					return true;
			}

			return false;
		}

		template<class T>
		static inline bool Contains(const std::vector<T>* vector, const T& item)
		{
			for (int index = 0; index < vector->size(); index++)
			{
				if (item == vector->at(index))
					return true;
			}

			return false;
		}

		template<class T>
		static inline std::vector<T> Append(const std::vector<T>& v1, const std::vector<T>& v2)
		{
			std::vector<T> vector = v1;
			for (int index = 0; index < v2.size(); index++)
				vector.push_back(v2[index]);

			return vector;
		}

		template<class T>
		static inline std::vector<T> Append(const std::vector<T>* v1, const std::vector<T>& v2)
		{
			std::vector<T> vector = &v1;
			for (int index = 0; index < v2.size(); index++)
				vector.push_back(v2[index]);

			return vector;
		}

		template<class T>
		static inline std::vector<T> Append(const std::vector<T>& v1, const std::vector<T>* v2)
		{
			std::vector<T> vector = v1;
			for (int index = 0; index < v2->size(); index++)
				vector.push_back(v2->at(index));

			return vector;
		}

		template<class T>
		static inline std::vector<T> Append(const std::vector<T>* v1, const std::vector<T>* v2)
		{
			std::vector<T> vector = &v1;
			for (int index = 0; index < v2->size(); index++)
				vector.push_back(v2->at(index));

			return vector;
		}

		template<class T>
		static inline void AddRange(std::vector<T>& v1, const std::vector<T>& v2)
		{
			for (int index = 0; index < v2.size(); index++)
				v1.push_back(v2[index]);
		}

		template<class T>
		static inline void AddRange(std::vector<T>* v1, const std::vector<T>& v2)
		{
			for (int index = 0; index < v2.size(); index++)
				v1->push_back(v2[index]);
		}

		template<class T>
		static inline void AddRange(std::vector<T>& v1, const std::vector<T>* v2)
		{
			for (int index = 0; index < v2->size(); index++)
				v1.push_back(v2->at(index));
		}

		template<class T>
		static inline void AddRange(std::vector<T>* v1, const std::vector<T>* v2)
		{
			for (int index = 0; index < v2->size(); index++)
				v1->push_back(v2->at(index));
		}

		template<class T, class F>
		static inline std::vector<T> Where(const std::vector<T>& vector, F check)
		{
			std::vector<T> output;
			for (int index = 0; index < vector.size(); index++)
			{
				if (check(vector[index]))
					output.push_back(vector[index]);
			}

			return output;
		}

		template<class T, class F>
		static inline std::vector<T> Where(const std::vector<T>* vector, F check)
		{
			std::vector<T> output;
			for (int index = 0; index < vector->size(); index++)
			{
				if (check(vector->at(index)))
					output.push_back(vector->at(index));
			}

			return output;
		}

		template<class T, class F>
		static inline std::vector<int> WhereIndicies(const std::vector<T>& vector, F check)
		{
			std::vector<int> output;
			for (int index = 0; index < vector.size(); index++)
			{
				if (check(vector[index]))
					output.push_back(index);
			}

			return output;
		}

		template<class T, class F>
		static inline std::vector<int> WhereIndicies(const std::vector<T>* vector, F check)
		{
			std::vector<int> output;
			for (int index = 0; index < vector->size(); index++)
			{
				if (check(vector->at(index)))
					output.push_back(index);
			}

			return output;
		}

		template<class T, class R, class F>
		static inline void Select(const std::vector<T>& vector, std::vector<R>& output, F action)
		{
			output.clear();
			for (int index = 0; index < vector.size(); index++)
				output.push_back(action(vector[index]));
		}

		template<class T, class R, class F>
		static inline void Select(const std::vector<T>* vector, std::vector<R>& output, F action)
		{
			output.clear();
			for (int index = 0; index < vector->size(); index++)
				output.push_back(action(vector->at(index)));
		}

		template<class T, class R, class F>
		static inline void Select(const std::vector<T>& vector, std::vector<R>* output, F action)
		{
			output->clear();
			for (int index = 0; index < vector.size(); index++)
				output->push_back(action(vector[index]));
		}

		template<class T, class R, class F>
		static inline void Select(const std::vector<T>* vector, std::vector<R>* output, F action)
		{
			output->clear();
			for (int index = 0; index < vector->size(); index++)
				output->push_back(action(vector->at(index)));
		}

		template<class T, class F>
		static inline void Foreach(const std::vector<T>& vector, F action)
		{
			for (int index = 0; index < vector.size(); index++)
				action(vector[index]);
		}

		template<class T, class F>
		static inline void Foreach(const std::vector<T>* vector, F action)
		{
			for (int index = 0; index < vector->size(); index++)
				action(vector->at(index));
		}

		template<class T>
		static inline T Sum(const std::vector<T>& vector)
		{
			T output = vector[0];
			for (int index = 1; index < vector.size(); index++)
				output += vector[index];

			return output;
		}

		template<class T>
		static inline T Sum(const std::vector<T>* vector)
		{
			T output = vector->at(0);
			for (int index = 1; index < vector->size(); index++)
				output += vector->at(index);

			return output;
		}

		template<class T>
		static inline std::vector<T> Min(const std::vector<T>& left, const std::vector<T>& right)
		{
			std::vector<T> output = std::vector<T>(left.size() > right.size() ? left.size() : right.size());
			for (int index = 0; index < output.size(); index++)
			{
				if (index >= left.size())
					output[index] = right[index];
				else if (index >= right.size())
					output[index] = left[index];
				else
					output[index] = left[index] < right[index] ? left[index] : right[index];
			}

			return output;
		}

		template<class T>
		static inline std::vector<T> Min(const std::vector<T>* left, const std::vector<T>& right)
		{
			std::vector<T> output = std::vector<T>(left->size() > right.size() ? left->size() : right.size());
			for (int index = 0; index < output.size(); index++)
			{
				if (index >= left->size())
					output[index] = right[index];
				else if (index >= right.size())
					output[index] = left->at(index);
				else
					output[index] = left->at(index) < right[index] ? left->at(index) : right[index];
			}

			return output;
		}

		template<class T>
		static inline std::vector<T> Min(const std::vector<T>& left, const std::vector<T>* right)
		{
			std::vector<T> output = std::vector<T>(left.size() > right->size() ? left.size() : right->size());
			for (int index = 0; index < output.size(); index++)
			{
				if (index >= left.size())
					output[index] = right->at(index);
				else if (index >= right->size())
					output[index] = left[index];
				else
					output[index] = left[index] < right->at(index) ? left[index] : right->at(index);
			}

			return output;
		}

		template<class T>
		static inline std::vector<T> Min(const std::vector<T>* left, const std::vector<T>* right)
		{
			std::vector<T> output = std::vector<T>(left->size() > right->size() ? left->size() : right->size());
			for (int index = 0; index < output.size(); index++)
			{
				if (index >= left->size())
					output[index] = right->at(index);
				else if (index >= right->size())
					output[index] = left->at(index);
				else
					output[index] = left->at(index) < right->at(index) ? left->at(index) : right->at(index);
			}

			return output;
		}

		template<class T>
		static inline std::vector<T> Max(const std::vector<T>& left, const std::vector<T>& right)
		{
			std::vector<T> output = std::vector<T>(left.size() > right.size() ? left.size() : right.size());
			for (int index = 0; index < output.size(); index++)
			{
				if (index >= left.size())
					output[index] = right[index];
				else if (index >= right.size())
					output[index] = left[index];
				else
					output[index] = left[index] > right[index] ? left[index] : right[index];
			}

			return output;
		}

		template<class T>
		static inline std::vector<T> Max(const std::vector<T>* left, const std::vector<T>& right)
		{
			std::vector<T> output = std::vector<T>(left->size() > right.size() ? left->size() : right.size());
			for (int index = 0; index < output.size(); index++)
			{
				if (index >= left->size())
					output[index] = right[index];
				else if (index >= right.size())
					output[index] = left->at(index);
				else
					output[index] = left->at(index) > right[index] ? left->at(index) : right[index];
			}

			return output;
		}

		template<class T>
		static inline std::vector<T> Max(const std::vector<T>& left, const std::vector<T>* right)
		{
			std::vector<T> output = std::vector<T>(left.size() > right->size() ? left.size() : right->size());
			for (int index = 0; index < output.size(); index++)
			{
				if (index >= left.size())
					output[index] = right->at(index);
				else if (index >= right->size())
					output[index] = left[index];
				else
					output[index] = left[index] > right->at(index) ? left[index] : right->at(index);
			}

			return output;
		}

		template<class T>
		static inline std::vector<T> Max(const std::vector<T>* left, const std::vector<T>* right)
		{
			std::vector<T> output = std::vector<T>(left->size() > right->size() ? left->size() : right->size());
			for (int index = 0; index < output.size(); index++)
			{
				if (index >= left->size())
					output[index] = right->at(index);
				else if (index >= right->size())
					output[index] = left->at(index);
				else
					output[index] = left->at(index) > right->at(index) ? left->at(index) : right->at(index);
			}

			return output;
		}

		template <typename T>
		static void Remove(std::vector<T>* vec, size_t pos)
		{
			std::vector<T>::iterator it = vec->begin();
			std::advance(it, pos);
			vec.erase(it);
		}

		template <typename T>
		static void Remove(std::vector<T>& vec, size_t pos)
		{
			std::vector<T>::iterator it = vec.begin();
			std::advance(it, pos);
			vec.erase(it);
		}

		template<class T>
		static inline void RemoveItem(std::vector<T>* vector, const T& item)
		{
			auto index = std::find(vector->begin(), vector->end(), item);
			if (index != vector->end())
				vector->erase(index);
		}

		template<class T>
		static inline void RemoveItem(std::vector<T>& vector, const T& item)
		{
			auto index = std::find(vector.begin(), vector.end(), item);
			if (index != vector.end())
				vector.erase(index);
		}
	};
}