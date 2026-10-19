# Fake match: Random called with an argument

`src/enemy/enemy_02042318.c` and `src/enemy/enemy_02042f30.c` call `Random` (0x0208455c, no parameters) through
`RANDOM_WITH_ARG(x)`, which casts it to take one `u32`. The original code has the value in `r0` before the `bl`, and this
is the only shape found so far that reproduces it. The real source probably computes that value as part of a
different expression; replace the macro once it is found.
