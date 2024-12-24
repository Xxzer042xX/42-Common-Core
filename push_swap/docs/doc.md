// operations.c
#include "push_swap.h"

void sa(t_stack *a)
{
    t_node *first;
    t_node *second;

    if (!a || !a->head || !a->head->next)
        return ;
    first = a->head;
    second = first->next;
    first->next = second->next;
    second->next = first;
    a->head = second;
    write(1, "sa\n", 3);
}

void sb(t_stack *b)
{
    t_node *first;
    t_node *second;

    if (!b || !b->head || !b->head->next)
        return ;
    first = b->head;
    second = first->next;
    first->next = second->next;
    second->next = first;
    b->head = second;
    write(1, "sb\n", 3);
}

void ss(t_stack *a, t_stack *b)
{
    t_node *first;
    t_node *second;

    if (a && a->head && a->head->next)
    {
        first = a->head;
        second = first->next;
        first->next = second->next;
        second->next = first;
        a->head = second;
    }
    if (b && b->head && b->head->next)
    {
        first = b->head;
        second = first->next;
        first->next = second->next;
        second->next = first;
        b->head = second;
    }
    write(1, "ss\n", 3);
}


// utils.c
#include "push_swap.h"

t_stack *init_stack(char id)
{
    t_stack *stack;

    stack = (t_stack *)malloc(sizeof(t_stack));
    if (!stack)
        error_exit();
    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;
    stack->id = id;
    return (stack);
}

void free_stack(t_stack *stack)
{
    t_node *current;
    t_node *next;

    if (!stack)
        return ;
    current = stack->head;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(stack);
}

void error_exit(void)
{
    write(2, "Error\n", 6);
    exit(1);
}

int is_sorted(t_stack *stack)
{
    t_node *current;

    if (!stack || !stack->head)
        return (1);
    current = stack->head;
    while (current->next)
    {
        if (current->value > current->next->value)
            return (0);
        current = current->next;
    }
    return (1);
}

// parsing.c

#include "push_swap.h"

static int is_number(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

static int check_duplicate(t_stack *stack, int num)
{
    t_node *current;

    current = stack->head;
    while (current)
    {
        if (current->value == num)
            return (1);
        current = current->next;
    }
    return (0);
}

static void add_node(t_stack *stack, int value)
{
    t_node *new_node;
    
    new_node = (t_node *)malloc(sizeof(t_node));
    if (!new_node)
        error_exit();
    new_node->value = value;
    new_node->next = NULL;
    
    if (!stack->head)
    {
        stack->head = new_node;
        stack->tail = new_node;
    }
    else
    {
        stack->tail->next = new_node;
        stack->tail = new_node;
    }
    stack->size++;
}

// Parse une chaîne en vérifiant qu'elle ne dépasse pas les limites d'un int
static int parse_number(char *str, t_stack *stack)
{
    long num;
    int sign;
    int i;

    num = 0;
    sign = 1;
    i = 0;

    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (str[i] == '+')
        i++;

    while (str[i])
    {
        num = num * 10 + (str[i] - '0');
        if ((sign == 1 && num > MAX_INT) || 
            (sign == -1 && num * sign < MIN_INT))
            error_exit();
        i++;
    }
    num *= sign;
    
    if (check_duplicate(stack, num))
        error_exit();
    
    return (num);
}

// Fonction principale de parsing des arguments
t_stack *parse_args(int argc, char **argv)
{
    t_stack *stack;
    char **split;
    int i;
    int j;
    int num;

    stack = init_stack('a');
    i = 1;
    while (i < argc)
    {
        if (!is_number(argv[i]))
        {
            split = ft_split(argv[i], ' ');
            if (!split)
                error_exit();
            j = 0;
            while (split[j])
            {
                if (!is_number(split[j]))
                    error_exit();
                num = parse_number(split[j], stack);
                add_node(stack, num);
                j++;
            }
            free_split(split);
        }
        else
        {
            num = parse_number(argv[i], stack);
            add_node(stack, num);
        }
        i++;
    }
    return (stack);
}

// instruction_parser.c

#include "push_swap.h"

static int is_valid_instruction(char *str)
{
    return (!ft_strcmp(str, "sa") || !ft_strcmp(str, "sb") ||
            !ft_strcmp(str, "ss") || !ft_strcmp(str, "pa") ||
            !ft_strcmp(str, "pb") || !ft_strcmp(str, "ra") ||
            !ft_strcmp(str, "rb") || !ft_strcmp(str, "rr") ||
            !ft_strcmp(str, "rra") || !ft_strcmp(str, "rrb") ||
            !ft_strcmp(str, "rrr"));
}

static void execute_instruction(char *instruction, t_stack *a, t_stack *b)
{
    if (!ft_strcmp(instruction, "sa")) sa(a);
    else if (!ft_strcmp(instruction, "sb")) sb(b);
    else if (!ft_strcmp(instruction, "ss")) ss(a, b);
    else if (!ft_strcmp(instruction, "pa")) pa(a, b);
    else if (!ft_strcmp(instruction, "pb")) pb(a, b);
    else if (!ft_strcmp(instruction, "ra")) ra(a);
    else if (!ft_strcmp(instruction, "rb")) rb(b);
    else if (!ft_strcmp(instruction, "rr")) rr(a, b);
    else if (!ft_strcmp(instruction, "rra")) rra(a);
    else if (!ft_strcmp(instruction, "rrb")) rrb(b);
    else if (!ft_strcmp(instruction, "rrr")) rrr(a, b);
}

// Cette fonction sera utile pour le bonus checker
int read_and_execute_instructions(t_stack *a, t_stack *b)
{
    char *line;

    while ((line = get_next_line(0)))
    {
        // Enlever le \n à la fin de la ligne
        line[ft_strlen(line) - 1] = '\0';
        
        if (!is_valid_instruction(line))
        {
            free(line);
            return (0);
        }
        execute_instruction(line, a, b);
        free(line);
    }
    return (1);
}