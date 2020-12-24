#include <cstdio>

bool isPlain (int c) {
  if (c >= 'a' && c <= 'z') return 1;
  if (c >= 'A' && c <= 'Z') return 1;
  if (c >= '0' && c <= '9') return 1;
  if (c == '(' || c == ')') return 1;
  if (c == ';' || c == ':' || c == ',' || c == '.' || c == '\'' || c == '?' || c == '-' || c == '!') return 1;
    if (c == ' ') return 1;
  return 0;
}

int main () {
  int n;
  scanf ("%d", &n);
  
  int a[n];
  for (int i=0; i<n; i++) scanf ("%d", a + i);
  
  int ans[3];
  for (int i=0; i<3; i++) {
    for (ans[i] = 'a'; ans[i] < 'z'; ans[i]++) {
      bool ok = 1;
      for (int j=i; j<n; j+=3) ok &= isPlain(a[j] ^ ans[i]);
      if (ok) break;
    }
    printf ("%c", ans[i]);
  }
    
  return 0;
}
