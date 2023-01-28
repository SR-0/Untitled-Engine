-- Dev - SR_0
-- Source(s) - https://www.youtube.com/watch?v=kDHGfHxwymI\



--print "Hello, World!"

-- "nil" is a special singleton value and is basically to Lua as nullptr is to C++
local object = nil

-- boolean(s)/bool(s) can equate to 'true' or 'false'
running = false

-- this just in... integer(s)
--windowWidth = 1020
--windowHeight = 1080
runInterval = 3.0

print "luaScript1"
--
---- talk of floating point number(s), more at 11:00
--pi = 3.141592
--
---- now to Bob for parameter passing - "it's double dotted fun, Steve"
----print("x = " .. x)
--
---- some funky func vibes (tutorial says "functions are first-class objects in Lua")
--function funcSum(a, b)
--	return a + b
--end
--
---- test
--l = 2
--r = 3
--
---- test
----print(l .. " + " .. r .. " = " .. funcSum(l, r))
--
---- tables can be lists
--primes = { 2, 3, 5, 7, 11 }
--
---- tables can be dictionaries, and the keys can be anything
--key = { 1, 2, 3 }
--record = 
--{
--	job = "developer",
--	[42] = "answer",
--	[key] = "you found key list!",
--}

-- printy print listy list thingy things (don't worry, I'll delete these cringe comments soon-ish)
--print("record['job'] = '" .. record['job'] .. "'")
--print("record[42] = '" .. record[42] .. "'")

-- indexing is by reference, not by value
--print("record[{1, 2, 3}] = " .. tostring(record[{1, 2, 3}]))
--print("record[key] = '" .. record[key] .. "'")

-- functions can return mutliple return values
function first_two(list)
	return list[1], list[2]
end

-- the "print" library function can deal with mutliple arguments (but not in the same line without separation on first try? I'll look into it)
--print("first two primes are:")
--print(first_two(primes))

--timeSinceLastCall = os.clock();