# -*- encoding: utf-8 -*-


import textwrap


def main():
    key_words = {3: "Fizz", 5: "Buzz"}
    fizzbuzz = {n: "".join(["" if n%i else mess for i, mess in key_words.items()]) for n in range(1, 51)}
    print(textwrap.fill(repr(fizzbuzz), 80))


if __name__ == "__main__":
    main()
