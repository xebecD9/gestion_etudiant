
void triAlphabetique(Etudiant T[], int n)
{
    int i, j;
    Etudiant temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(T[i].nom, T[j].nom) > 0)
            {
                temp = T[i];
                T[i] = T[j];
                T[j] = temp;
            }
        }
    }
    int rechercheDichotomique(Etudiant T[], int n, char nomRech[])
    {
        int debut = 0, fin = n - 1, mid;
        while (debut <= fin)
        {
            mid = (debut + fin) / 2;
            if (strcmp(T[mid].nom, nomRech) == 0)
            {
                return mid;
            }
            else if (strcmp(T[mid].nom, nomRech) < 0)
            {
                debut = mid + 1;
            }
            else
            {
                fin = mid - 1;
            }
        }
        return -1;
    }
    void triParFiliere(Etudiant T[], int n)
    {
        int i, j;
        Etudiant temp;
        for (i = 0; i < n - 1; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                if (strcmp(T[i].filiere, T[j].filiere) > 0)
                {
                    temp = T[i];
                    T[i] = T[j];
                    T[j] = temp;
                }
            }
        }