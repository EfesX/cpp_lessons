/** @file main.cpp 
 * @brief asdasda
*/

#include <iostream>
#include <vector>
#include <list>
#include <tuple>

//**********************************************************
//template<typename _T, typename = typename _T::iterator>   
//void print_ip(_T value) {
//	cout << __PRETTY_FUNCTION__ << endl;
//}
//***********************************************************
//template<typename T>
//void print_ip(T container, typename T::iterator* = nullptr) {
//	cout << __PRETTY_FUNCTION__ << endl;
//}
//***********************************************************

/**
 * @brief Вспомогательная метафункция для печати контейнеров
*/
template <typename T>
struct _print_container {
	static void print(const T& container){
		for (auto it = container.begin(); it != container.end(); it++){
			std::cout << *it;
			if(it != (--container.end())) std::cout << '.';
		}
		std::cout << std::endl;
	};
};

/**
 * @brief Уточнение метафункции для реализации печати строк
*/
template <>
struct _print_container<std::string> {
	static void print(const std::string& container){
		std::cout << container << std::endl;
	};
};

/**
 * @brief Вспомогательная метафункция для печати кортежей.
 * 		Вызывается один раз в конце рекурсивных вызовов
*/
template<std::size_t I = 0, typename... Tp>
typename std::enable_if<I == sizeof...(Tp), void>::type
_print_tuple(const std::tuple<Tp...>&) {
	std::cout << std::endl;
}

/**
 * @brief Вспомогательная метафункция для печати кортежей
 * 		Вызывается рекурсивно
*/
template<std::size_t I = 0, typename... Tp> typename std::enable_if<I < sizeof...(Tp), void>::type
_print_tuple(const std::tuple<Tp...> &t){
	std::cout << std::get<I>(t);

	if (I != ((sizeof...(Tp)) - 1))
		std::cout << '.';

	_print_tuple<I + 1, Tp...>(t);
}

/**
 * @brief Функция проверки на то, что все элементы кортежа имеют одинаковый тип
*/
template<typename TT, std::size_t index = std::tuple_size_v<TT>> 
constexpr bool check_types(){
	if constexpr (index == 0) return true;
	else if constexpr (
		!std::is_same_v<
			std::tuple_element_t<index - 1, TT>, 
			std::tuple_element_t<0, TT>
		>
	) return false;
	else return check_types<TT, index - 1>();
}

/**
 * @brief Функция для печати контейнеров и строк
*/
template <typename T>
decltype(std::declval<T>().begin(), std::declval<T>().end(), void())
print_ip(const T& container){
	_print_container<T>::print(container);
}

/**
 * @brief Функция для печати целочисленных значений
*/
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_ip(const T& intvalue) {
	for (auto i = 0; i < sizeof(intvalue); i++){
		auto offset = (sizeof(intvalue) << 3) - 8 - (i << 3);
	
		std::cout << ((intvalue >> offset) & 0xff);
	
		if(i != (sizeof(intvalue) - 1)) std::cout << '.';
	}
	std::cout << std::endl;
}

/**
 * @brief Функция для печати кортежей
*/
template<std::size_t I = 0, typename... Tp>
typename std::enable_if<I < sizeof...(Tp), void>::type
print_ip(std::tuple<Tp...> tuple){
	static_assert(
		check_types<decltype(tuple)>(), 
		"Все элементы кортежа должны быть одного типа"
	);
	_print_tuple(tuple);
}

/**
 * @brief Entry point
 * @return Program exit status
*/
int main(void)
{
    print_ip(int8_t{-1});
    print_ip(int16_t{0});
	print_ip(int32_t{2130706433});
	print_ip(int64_t{8875824491850138409});
	print_ip(std::string{"Hello, World!"});
	print_ip(std::vector<int>{100, 200, 300, 400});
	print_ip(std::list<short>{400, 300, 200, 100});
	print_ip(std::make_tuple(123, 456, 789, 0));
	//print_ip(std::make_tuple(123, 456, "asd", 0));

    return 0;
}
