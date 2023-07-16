#!/usr/bin/python3
from pygpmp import nt


def main():
    p = nt.PrimalityTest()

    prime_0 = p.is_prime(2999)
    prime_1 = p.carmichael_num(561)
    print(prime_0)
    print(prime_1)

    mod_0 = p.mod_pow(3, 2, 2)
    mod_1 = p.mod_pow(5, 2, 7)
    print(mod_0)
    print(mod_1)

    p.miller_rabin(4, 4, 200)

    ss_0 = p.solovoy_strassen(15, 50)
    ss_1 = p.solovoy_strassen(1049, 50)
    print(ss_0)
    print(ss_1)


if __name__ == "__main__":
    main()
