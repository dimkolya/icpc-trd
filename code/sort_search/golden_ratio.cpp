ld d = 2 - numbers::phi_v<ld>;
ld x1 = l + d * (r - l), x2 = r - d * (r - l);
ld f1 = f(x1), f2 = f(x2);
while (r - l > EPS) {
  if (f1 < f2) {
    r = x2; x2 = x1, f2 = f1;
    x1 = l + d * (r - l); f1 = f(x1);
  } else {
    l = x1; x1 = x2, f1 = f2;
    x2 = r - d * (r - l); f2 = f(x2);
  }
}