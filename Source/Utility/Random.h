/*
    file: random_number_generator.hpp
    author(s): SR_0
    version: 0.0.1

    - v - DESCRIPTION - v -
    @TODO
    - ^ - DESCRIPTION - ^ -

    using namespace(s): std
    declared struct(s): N/A
    declared class(es):

        - random_number_generator
        - random_number_generator_fixed_range
        - static_random_number_generator
        - static_random_number_generator_fixed_range

    declared alias(es):

        - random_number_generator
          \
            - rng
              \
                - rng_short
                - rng_int
                - rng_long
                - rng_long_long
                - rng_unsigned_short
                - rng_unsigned_int
                - rng_unsigned_long
                - rng_unsigned_long_long
                - rng_int16_t
                - rng_int32_t
                - rng_int64_t
                - rng_uint16_t
                - rng_uint32_t
                - rng_uint64_t
                - rng_float
                - rng_double
                - rng_long_double

        - random_number_generator_fixed_range
          \
            - rngfr

        - static_random_number_generator
          \
            - srng
              \
                - srng_short
                - srng_int
                - srng_long
                - srng_long_long
                - srng_unsigned_short
                - srng_unsigned_int
                - srng_unsigned_long
                - srng_unsigned_long_long
                - srng_int16_t
                - srng_int32_t
                - srng_int64_t
                - srng_uint16_t
                - srng_uint32_t
                - srng_uint64_t
                - srng_float
                - srng_double
                - srng_long_double

        - static_random_number_generator_fixed_range
          \
            - srngfr

    - v - CHANGE LOG - v -
    @TODO
    - ^ - CHANGE LOG - ^ -

    additional note(s): N/A
*/

#pragma once

#include <cstdint>
#include <random>
#include <type_traits>

#pragma region random_number_generator

template
<
	typename value_type,
	typename generator_type = std::default_random_engine
>
class random_number_generator
{
public:

	using distribution_type = typename std::conditional
	<
		std::is_integral<value_type>::value,
		std::uniform_int_distribution<value_type>,
		std::uniform_real_distribution<value_type>
	>
	::type;

private:

	std::random_device random_device;
	generator_type generator = generator_type{ random_device() };

public:

	const value_type range
	(
		value_type min = std::numeric_limits<value_type>::min(),
		value_type max = std::numeric_limits<value_type>::max()
	)
	{
		distribution_type distribution{ min, max };
		return distribution(generator);
	}

};

template
<
	typename value_type,
	typename generator_type = std::default_random_engine
>
using rng = random_number_generator<value_type, generator_type>;

using rng_short                 = rng<short>;
using rng_int                   = rng<int>;
using rng_long                  = rng<long>;
using rng_long_long             = rng<long long>;
using rng_unsigned_short        = rng<unsigned short>;
using rng_unsigned_int          = rng<unsigned int>;
using rng_unsigned_long         = rng<unsigned long>;
using rng_unsigned_long_long    = rng<unsigned long long>;
using rng_int16_t               = rng<std::int16_t>;
using rng_int32_t               = rng<std::int32_t>;
using rng_int64_t               = rng<std::int64_t>;
using rng_uint16_t              = rng<std::uint16_t>;
using rng_uint32_t              = rng<std::uint32_t>;
using rng_uint64_t              = rng<std::uint64_t>;
using rng_float                 = rng<float>;
using rng_double                = rng<double>;
using rng_long_double           = rng<long double>;

#pragma endregion random_number_generator



#pragma region random_number_generator_fixed_range

template
<
	typename value_type,
	value_type min = std::numeric_limits<value_type>::min(),
	value_type max = std::numeric_limits<value_type>::max(),
	typename generator_type = std::default_random_engine
>
class random_number_generator_fixed_range
{
public:

	using distribution_type = typename std::conditional
	<
		std::is_integral<value_type>::value,
		std::uniform_int_distribution<value_type>,
		std::uniform_real_distribution<value_type>
	>
	::type;

private:

	std::random_device random_device;
	generator_type generator = generator_type{ random_device() };
	distribution_type distribution{ min, max };

public:

	const value_type value()
	{
		return distribution(generator);
	}

};

template
<
	typename value_type,
	value_type min = std::numeric_limits<value_type>::min(),
	value_type max = std::numeric_limits<value_type>::max(),
	typename generator_type = std::default_random_engine
>
using rngfr = random_number_generator_fixed_range<value_type, min, max, generator_type>;

#pragma endregion random_number_generator_fixed_range



#pragma region static_random_number_generator

template
<
	typename value_type,
	typename generator_type = std::default_random_engine
>
class static_random_number_generator
{
public:

	using distribution_type = typename std::conditional
	<
		std::is_integral<value_type>::value,
		std::uniform_int_distribution<value_type>,
		std::uniform_real_distribution<value_type>
	>
	::type;

public:

	static value_type range
	(
		value_type min = std::numeric_limits<value_type>::min(),
		value_type max = std::numeric_limits<value_type>::max()
	)
	{
		static std::random_device random_device;
		static generator_type generator = generator_type{ random_device() };
		distribution_type distribution{ min, max };
		return distribution(generator);
	}

};

template
<
	typename value_type,
	typename generator_type = std::default_random_engine
>
using srng = static_random_number_generator<value_type, generator_type>;
 
using srng_short                = srng<short>;
using srng_int                  = srng<int>;
using srng_long                 = srng<long>;
using srng_long_long            = srng<long long>;
using srng_unsigned_short       = srng<unsigned short>;
using srng_unsigned_int         = srng<unsigned int>;
using srng_unsigned_long        = srng<unsigned long>;
using srng_unsigned_long_long   = srng<unsigned long long>;
using srng_int16_t              = srng<std::int16_t>;
using srng_int32_t              = srng<std::int32_t>;
using srng_int64_t              = srng<std::int64_t>;
using srng_uint16_t             = srng<std::uint16_t>;
using srng_uint32_t             = srng<std::uint32_t>;
using srng_uint64_t             = srng<std::uint64_t>;
using srng_float                = srng<float>;
using srng_double               = srng<double>;
using srng_long_double          = srng<long double>;

#pragma endregion static_random_number_generator



#pragma region static_random_number_generator_fixed_range

template
<
	typename value_type,
	value_type min = std::numeric_limits<value_type>::min(),
	value_type max = std::numeric_limits<value_type>::max(),
	typename generator_type = std::default_random_engine
>
class static_random_number_generator_fixed_range
{
public:

	using distribution_type = typename std::conditional
	<
		std::is_integral<value_type>::value,
		std::uniform_int_distribution<value_type>,
		std::uniform_real_distribution<value_type>
	>
	::type;

public:

	static value_type value()
	{
		static std::random_device random_device;
		static generator_type generator = generator_type{ random_device() };
		static distribution_type distribution{ min, max };
		return distribution(generator);
	}

};

template
<
	typename value_type,
	value_type min = std::numeric_limits<value_type>::min(),
	value_type max = std::numeric_limits<value_type>::max(),
	typename generator_type = std::default_random_engine
>
using srngfr = static_random_number_generator_fixed_range<value_type, min, max, generator_type>;

#pragma endregion static_random_number_generator_fixed_range