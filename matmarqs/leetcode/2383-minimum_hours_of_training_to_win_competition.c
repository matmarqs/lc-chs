#include <stdio.h>

#define print_var(var) do { printf(#var " = %d\n", (var)); } while (0)
#define print_array(arr, arrsize)                                   \
    do {                                                            \
        printf("%s = [ ", #arr);                                    \
        for (size_t i = 0; i < (arrsize); ++i) {                    \
            printf("%d", (arr)[i]);                                 \
            if (i < (arrsize) - 1) printf(", ");                    \
        }                                                           \
        printf(" ]\n");                                             \
    } while (0)

/***********************************************/

int max(int a, int b) {
    return a > b ? a : b;
}

int minNumberOfHours(int initialEnergy, int initialExperience, int* energy, int energySize, int* experience, int experienceSize) {
    /* we need both STRICTLY greater experience and energy */
    /* so, the minimum energy we need is sum(E in energy) + 1 */
    /* now, let x be the initial experience */
    /* x then has to satisfy the following set of inequalities */
    /* let sum_xp[i] = sum([experience[j] for j in range(i)]) */
    /* x > experience[0]  ->  x >= experience[0] + 1 */
    /* x + experience[0] > experience[1]  ->  x >= experience[1] - (experience[0]) + 1 */
    /* x + experience[0] + experience[1] > experience[2]  ->  x >= experience[2] - (experience[0] + experience[1]) + 1 */
    /* x + sum([experience[j] for j in range(i)]) > experience[i]  ->  x >= experience[i] - sum_xp[i] + 1   */
    /* therefore, x is the max(experience[i] - sum_xp[i] + 1) for all i */

    int minimum_energy = 1;
    for (int i = 0; i < energySize; i++) {
        minimum_energy += energy[i];
    }

    //print_array(experience, experienceSize);
    //print_array(energy, energySize);

    int minimum_xp = 0;
    int sum_xp = 0;
    for (int i = 0; i < experienceSize; i++) {
        minimum_xp = max(minimum_xp, experience[i] - sum_xp + 1);
        //print_var(experience[i] - sum_xp + 1);
        //print_var(sum_xp);
        //print_var(minimum_xp);
        sum_xp += experience[i];
    }

    int training_hours = max(0, minimum_energy - initialEnergy) + max(0, minimum_xp - initialExperience);

    //print_var(minimum_energy);
    //print_var(minimum_xp);
    //print_var(training_hours);

    return training_hours;

    /* observation: if we could choose which opponents to fight */
    /* of course, it's better to first fight against the competitors that have less experience */
    /* so, in that case we would first sort the array experience[i] by experience */
}


/****************************************/

int main() {
    int energy[4] = {1, 4, 3, 2};
    int experience[4] = {2, 6, 3, 1};
    minNumberOfHours(5, 3, energy, 4, experience, 4);
    return 0;
}
