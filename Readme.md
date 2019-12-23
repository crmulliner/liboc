# liboc - open count

small LD_PRELOAD library that counts the number of open(2) calls and returns EACCESS
after _N_ calls, _N_ can be defined via the OC_OPEN_COUNT environment variable.

See [test/test.sh](test/test.sh).

Based on the disucssion with Chris Rohlf on [twitter](https://twitter.com/chrisrohlf/status/1206610746379055104).

