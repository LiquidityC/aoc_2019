#include <stdio.h>
#include <stdlib.h>
#include <libinput.h>
#include <stdbool.h>
#include <stdint.h>

int main()
{
	FILE *fp = fopen("input.txt", "r");
	Lines *l = lines_read(fp);
	int *containers = malloc(sizeof(int) * l->size);
	int ccount = l->size;
	for (int i = 0; i < ccount; ++i) {
		sscanf(l->lines[i], "%d", &containers[i]);
	}
	fclose(fp);
	lines_free(l);

	int *min_container_counts = calloc(20, sizeof(int));

	int combo_count = 0;
	int total, t, container_count;
	for (int i = 0; i < (1 << ccount); ++i) {
		total = 0;
		t = i;
		container_count = 0;
		for (int j = 0; j < ccount; ++j) {
			if ((t % 2) == 1) {
				total += containers[j];
				container_count += 1;
			}
			t /= 2;
		}
		if (total == 150) {
			combo_count += 1;
			min_container_counts[container_count-1]++;
		}
	}

	//int count = perfect_fill(containers, ccount, 150);
	printf("Part 1: %d\n", combo_count);
	free(containers);

	for (int i = 0; i < ccount; ++i) {
		if (min_container_counts[i] > 0) {
			printf("Part 2: %d\n", min_container_counts[i]);
			break;
		}
	}
	free(min_container_counts);
}
