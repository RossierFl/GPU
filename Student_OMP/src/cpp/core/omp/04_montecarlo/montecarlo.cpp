#include "OmpTools.h"
#include <stdio.h>

float f(float x) {
	return 0.3;
}

float montecarlo(const float X_MIN, const float X_MAX, const int M, const unsigned long long N) {
	unsigned int nb = 0;

	for (unsigned long long i = 0; i < N; i++) {
		const float X_ALEA = OmpTools::uniform(X_MIN, X_MAX);
		const float Y_ALEA = OmpTools::uniform(0, M);
		if (Y_ALEA < f(X_ALEA)) {
			nb++;
		}
	}

	return (float) nb / N * (X_MAX - X_MIN) * M;
}

bool useMontecarlo() {
	const unsigned long long N = 5000000;
	float res = montecarlo(0, 2, 1, N);
	printf("%f\n", res);

	return true;
}

