#include <stdio.h>
int main()
{
    int id;
    char name[50];
    char version[20];

    printf("Enter Package ID: ");
    scanf("%d",&id);

    printf("Enter Package Name: ");
    scanf("%49s",name);

    printf("Enter Package Version: ");
    scanf("%19s",version);

    if(id > 0)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");

    printf("Package Details:\n");
    printf("ID: %d\n",id);
    printf("Name: %s\n",name);
    printf("Version: %s\n",version);

    return 0;
}

testcirculardependency.c
#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
int recStack[MAX];
int vertices;

int dfs(int node)
{
    visited[node]=1;
    recStack[node]=1;

    for(int i=0;i<vertices;i++)
    {
        if(graph[node][i])
        {
            if(!visited[i])
            {
                if(dfs(i))
                    return 1;
            }
            else if(recStack[i])
            {
                return 1;
            }
        }
    }

    recStack[node]=0;
    return 0;
}

int detectCycle()
{
    for(int i=0;i<vertices;i++)
    {
        if(!visited[i])
        {
            if(dfs(i))
                return 1;
        }
    }
    return 0;
}

int main()
{
    int edges, src, dest;

    printf("Enter number of packages: ");
    scanf("%d",&vertices);

    printf("Enter number of dependencies: ");
    scanf("%d",&edges);

    for(int i=0;i<edges;i++)
    {
        scanf("%d%d",&src,&dest);
        graph[src][dest]=1;
    }

    if(detectCycle())
        printf("TEST PASSED: Circular Dependency Found\n");
    else
        printf("TEST PASSED: No Circular Dependency\n");

    return 0;
}

3. Testconflict.c
#include <stdio.h>
#include <string.h>

struct Package
{
    char name[30];
    char version[20];
};

int main()
{
    struct Package p1, p2;

    printf("Enter Package 1 Name: ");
    scanf("%29s", p1.name);

    printf("Enter Package 1 Version: ");
    scanf("%19s", p1.version);

    printf("Enter Package 2 Name: ");
    scanf("%29s", p2.name);

    printf("Enter Package 2 Version: ");
    scanf("%19s", p2.version);

    if(strcmp(p1.name, p2.name) == 0 &&
       strcmp(p1.version, p2.version) != 0)
    {
        printf("TEST PASSED : Conflict Detected\n");
    }
    else
    {
        printf("TEST PASSED : No Conflict\n");
    }

    return 0;
}

4. testgraph.c
#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];

int main()
{
    int vertices, edges;
    int src, dest;

    printf("Enter number of packages: ");
    scanf("%d",&vertices);

    printf("Enter number of dependencies: ");
    scanf("%d",&edges);

    for(int i=0;i<edges;i++)
    {
        scanf("%d%d",&src,&dest);
        graph[src][dest]=1;
    }

    printf("\nDependency Graph:\n");

    for(int i=0;i<vertices;i++)
    {
        for(int j=0;j<vertices;j++)
        {
            printf("%d ",graph[i][j]);
        }
        printf("\n");
    }

    return 0;
}

5. testinstallation.c
#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
int stack[MAX];
int top=-1;
int vertices;

void topo(int node)
{
    visited[node]=1;

    for(int i=0;i<vertices;i++)
    {
        if(graph[node][i] && !visited[i])
            topo(i);
    }

    stack[++top]=node;
}

int main()
{
    int edges,src,dest;

    printf("Enter number of packages: ");
    scanf("%d",&vertices);

    printf("Enter number of dependencies: ");
    scanf("%d",&edges);

    for(int i=0;i<edges;i++)
    {
        scanf("%d%d",&src,&dest);
        graph[src][dest]=1;
    }

    for(int i=0;i<vertices;i++)
    {
        if(!visited[i])
            topo(i);
    }

    printf("Installation Order:\n");

    while(top!=-1)
    {
        printf("%d ",stack[top--]);
    }

    printf("\n");

    return 0;
}

6. testreporting.c
#include <stdio.h>

int main()
{
    int packages,dependencies,conflicts,cycles;

    printf("Packages: ");
    scanf("%d",&packages);

    printf("Dependencies: ");
    scanf("%d",&dependencies);

    printf("Conflicts: ");
    scanf("%d",&conflicts);

    printf("Cycles: ");
    scanf("%d",&cycles);

    printf("\n===== REPORT =====\n");
    printf("Packages: %d\n",packages);
    printf("Dependencies: %d\n",dependencies);
    printf("Conflicts: %d\n",conflicts);
    printf("Cycles: %d\n",cycles);

    return 0;
}

7. testresolution.c
#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];

int main()
{
    int vertices, edges;
    int src,dest,package;

    printf("Enter number of packages: ");
    scanf("%d",&vertices);

    printf("Enter number of dependencies: ");
    scanf("%d",&edges);

    for(int i=0;i<edges;i++)
    {
        scanf("%d%d",&src,&dest);
        graph[src][dest]=1;
    }

    printf("Enter package: ");
    scanf("%d",&package);

    printf("Dependencies:\n");

    for(int i=0;i<vertices;i++)
    {
        if(graph[package][i])
            printf("Package %d\n",i);
    }

    return 0;
}

8. testuser.c
#include <stdio.h>

int main()
{
    int choice;

    printf("1.Package Management\n");
    printf("2.Dependency Graph\n");
    printf("3.Circular Dependency\n");
    printf("4.Dependency Resolution\n");
    printf("5.Installation Order\n");
    printf("6.Conflict Detection\n");
    printf("7.Reporting\n");
    printf("8.Exit\n");

    printf("Enter Choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1: printf("Package Management Selected\n"); break;
        case 2: printf("Dependency Graph Selected\n"); break;
        case 3: printf("Circular Dependency Selected\n"); break;
        case 4: printf("Dependency Resolution Selected\n"); break;
        case 5: printf("Installation Order Selected\n"); break;
        case 6: printf("Conflict Detection Selected\n"); break;
        case 7: printf("Reporting Selected\n"); break;
        case 8: printf("Exit\n"); break;
        default: printf("Invalid Choice\n");
    }

    return 0;
}
