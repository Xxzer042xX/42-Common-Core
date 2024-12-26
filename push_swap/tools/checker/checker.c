/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 09:44:05 by madelmen          #+#    #+#             */
/*   Updated: 2024/12/26 09:44:05 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include "../lib/libftprintf/include/ft_printf.h"

typedef struct s_stack
{
    int             *numbers;
    int             size;
    struct s_stack  *next;
} t_stack;

// Fonctions principales
int     parse_args(int argc, char **argv, t_stack *stack_a);
int     execute_instructions(t_stack *stack_a, t_stack *stack_b);
int     is_sorted(t_stack *stack);

// Opérations de pile
void    sa(t_stack *stack_a, int print);
void    sb(t_stack *stack_b, int print);
void    ss(t_stack *stack_a, t_stack *stack_b, int print);
void    pa(t_stack *stack_a, t_stack *stack_b, int print);
void    pb(t_stack *stack_b, t_stack *stack_a, int print);
void    ra(t_stack *stack_a, int print);
void    rb(t_stack *stack_b, int print);
void    rr(t_stack *stack_a, t_stack *stack_b, int print);
void    rra(t_stack *stack_a, int print);
void    rrb(t_stack *stack_b, int print);
void    rrr(t_stack *stack_a, t_stack *stack_b, int print);

// Utilitaires
void    free_stack(t_stack *stack);
int     error_exit(t_stack *stack_a, t_stack *stack_b);



int main(int argc, char **argv)
{
    t_stack *stack_a;
    t_stack *stack_b;

    if (argc < 2)
        return (0);

    stack_a = malloc(sizeof(t_stack));
    stack_b = malloc(sizeof(t_stack));
    if (!stack_a || !stack_b)
        return (error_exit(stack_a, stack_b));

    stack_a->numbers = malloc(sizeof(int) * (argc - 1));
    stack_b->numbers = malloc(sizeof(int) * (argc - 1));
    if (!stack_a->numbers || !stack_b->numbers)
        return (error_exit(stack_a, stack_b));

    stack_a->size = 0;
    stack_b->size = 0;

    if (!parse_args(argc, argv, stack_a))
        return (error_exit(stack_a, stack_b));

    if (!execute_instructions(stack_a, stack_b))
        return (error_exit(stack_a, stack_b));

    if (is_sorted(stack_a) && stack_b->size == 0)
        ft_putendl_fd("OK", 1);
    else
        ft_putendl_fd("KO", 1);

    free_stack(stack_a);
    free_stack(stack_b);
    return (0);
}


void sa(t_stack *stack_a, int print)
{
    int temp;

    if (stack_a->size < 2)
        return;
    temp = stack_a->numbers[0];
    stack_a->numbers[0] = stack_a->numbers[1];
    stack_a->numbers[1] = temp;
    if (print)
        ft_putendl_fd("sa", 1);
}

// ... (autres opérations similaires)

int parse_args(int argc, char **argv, t_stack *stack_a)
{
    long num;
    int i;
    int j;

    i = 1;
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if ((argv[i][j] < '0' || argv[i][j] > '9') && 
                argv[i][j] != '-' && argv[i][j] != '+')
                return (0);
            j++;
        }
        num = ft_atoi(argv[i]);
        if (num > INT_MAX || num < INT_MIN)
            return (0);
        // Vérification des doublons
        for (j = 0; j < stack_a->size; j++)
            if (stack_a->numbers[j] == num)
                return (0);
        stack_a->numbers[stack_a->size++] = num;
        i++;
    }
    return (1);
}


int execute_instructions(t_stack *stack_a, t_stack *stack_b)
{
    char *line;
    int ret;

    while ((ret = get_next_line(0, &line)) > 0)
    {
        if (ft_strcmp(line, "sa") == 0)
            sa(stack_a, 0);
        else if (ft_strcmp(line, "sb") == 0)
            sb(stack_b, 0);
        // ... (autres instructions)
        else
        {
            free(line);
            return (0);
        }
        free(line);
    }
    if (ret == -1)
        return (0);
    return (1);
}



je vais te donner une 20 de fonctions


void __do_global_dtors_aux(void)

{
  if (completed.7698 != '\0') {
    return;
  }
  __cxa_finalize(__dso_handle);
  deregister_tm_clones();
  completed.7698 = 1;
  return;
}

void __libc_csu_fini(void)

{
  return;
}

void __libc_csu_init(EVP_PKEY_CTX *param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  
  _init(param_1);
  lVar1 = 0;
  do {
    (*(code *)(&__frame_dummy_init_array_entry)[lVar1])((ulong)param_1 & 0xffffffff,param_2,param_3)
    ;
    lVar1 = lVar1 + 1;
  } while (lVar1 != 1);
  return;
}

void _fini(void)

{
  return;
}

int _init(EVP_PKEY_CTX *ctx)

{
  int iVar1;
  
  iVar1 = __gmon_start__();
  return iVar1;
}

void processEntry _start(undefined8 param_1,undefined8 param_2)

{
  undefined auStack_8 [8];
  
  __libc_start_main(main,param_2,&stack0x00000008,__libc_csu_init,__libc_csu_fini,param_1,auStack_8)
  ;
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}
void a_to_b(long param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = pibon_index(param_1,0x61);
  uVar2 = top(param_1,0x61);
  uVar1 = pivot(param_1,0x61,uVar2,uVar1);
  while( true ) {
    iVar4 = pibon_index(param_1,0x61);
    if (iVar4 - *(int *)(param_1 + 0x28) < 2) break;
    iVar4 = check_order_stack(param_1);
    if (iVar4 != -1) break;
    *(undefined4 *)(param_1 + 0x44) = 0;
    uVar2 = sort_a_to_b(param_1,uVar1,0);
    rotate_pibon_min(param_1,uVar1,uVar2);
    if (*(int *)(param_1 + 0x20) != 0) {
      iVar4 = pibon_index(param_1,0x61);
      iVar3 = top(param_1,0x61);
      if (1 < iVar4 - iVar3) {
        operation(param_1,&DAT_00105600);
        push_operations(param_1,&DAT_00105600);
        add_pibon(param_1,uVar1);
      }
    }
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    uVar1 = pibon_a(param_1);
    *(undefined4 *)(param_1 + 0x30) = uVar1;
  }
  return;
}

void add_pibon(int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int local_14;
  
  local_14 = 1;
  iVar1 = checkmore(*(undefined8 *)(param_1 + 6),param_1[0xb],*param_1 + -1,param_2);
  if ((iVar1 == -1) &&
     (puVar2 = (undefined4 *)ft_init_int(param_1[0x12] + 1), puVar2 != (undefined4 *)0x0)) {
    *puVar2 = param_2;
    for (; local_14 < param_1[0x12] + 1; local_14 = local_14 + 1) {
      puVar2[local_14] = *(undefined4 *)(*(long *)(param_1 + 0xe) + (long)local_14 * 4 + -4);
    }
    free(*(void **)(param_1 + 0xe));
    *(undefined4 **)(param_1 + 0xe) = puVar2;
    param_1[0x12] = param_1[0x12] + 1;
  }
  return;
}

void b_to_a(long param_1,int param_2,int *param_3)

{
  undefined4 uVar1;
  
  if (*(int *)((long)*(int *)(param_1 + 0x2c) * 4 + *(long *)(param_1 + 0x18)) < param_2) {
    if (1 < *(int *)(param_1 + 0x24)) {
      operation(param_1,&DAT_001055ee);
      rotate_operations(param_1,&DAT_001055ee);
      *param_3 = *param_3 + 1;
    }
  }
  else {
    operation(param_1,&DAT_001055e2);
    push_operations(param_1,&DAT_001055e2);
    if (param_2 == *(int *)((long)*(int *)(param_1 + 0x28) * 4 + *(long *)(param_1 + 0x10))) {
      operation(param_1,&DAT_001055e6);
      rotate_operations(param_1,&DAT_001055e6);
      *(undefined4 *)(param_1 + 0x44) = 1;
    }
    if (*(int *)(((long)*(int *)(param_1 + 0x28) + 1) * 4 + *(long *)(param_1 + 0x10)) <
        *(int *)((long)*(int *)(param_1 + 0x28) * 4 + *(long *)(param_1 + 0x10))) {
      operation(param_1,&DAT_001055ea);
      swap_operations(param_1,&DAT_001055ea);
    }
    uVar1 = pibon_a(param_1);
    *(undefined4 *)(param_1 + 0x30) = uVar1;
  }
  return;
}

long bubble_sort(long param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 local_14;
  undefined4 local_10;
  
  for (local_14 = 0; local_10 = local_14, local_14 < param_2; local_14 = local_14 + 1) {
    while (local_10 = local_10 + 1, local_10 < param_2) {
      if (*(int *)(param_1 + (long)local_10 * 4) < *(int *)(param_1 + (long)local_14 * 4)) {
        uVar1 = *(undefined4 *)(param_1 + (long)local_14 * 4);
        *(undefined4 *)(param_1 + (long)local_14 * 4) =
             *(undefined4 *)(param_1 + (long)local_10 * 4);
        *(undefined4 *)((long)local_10 * 4 + param_1) = uVar1;
      }
    }
  }
  return param_1;
}


int calculate_the_pibon_stack_b(int *param_1)

{
  int iVar1;
  int local_c;
  
  if (param_1[0x12] < 2) {
    local_c = pivot(param_1,0x62,param_1[0xb],*param_1 + -1);
    add_pibon(param_1,local_c);
  }
  else {
    iVar1 = pibon_index(param_1,0x62);
    local_c = pivot(param_1,0x62,param_1[0xb],iVar1 + -1);
    if (local_c < **(int **)(param_1 + 0xe)) {
      local_c = **(int **)(param_1 + 0xe);
      remove_pibon(param_1);
    }
  }
  return local_c;
}

undefined8 check_atoi(char *param_1)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  int local_18;
  int local_14;
  
  local_18 = 0;
  local_14 = 0;
  if (((*param_1 == '+') || (*param_1 == '-')) && (iVar1 = ft_isdigit((int)param_1[1]), iVar1 == 1))
  {
    local_18 = 1;
  }
  for (; param_1[local_18] == '0'; local_18 = local_18 + 1) {
  }
  while (iVar1 = ft_isdigit((int)param_1[local_14 + local_18]), iVar1 != 0) {
    local_14 = local_14 + 1;
  }
  iVar1 = ft_isdigit((int)param_1[local_14 + local_18]);
  if ((iVar1 == 0) && (param_1[local_14 + local_18] != '\0')) {
    uVar2 = 0xffffffff;
  }
  else {
    lVar3 = ft_atol(param_1);
    if ((lVar3 < -0x80000000) || ((0x7fffffff < lVar3 || (10 < local_14)))) {
      uVar2 = 0xffffffff;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}


undefined8 check_double(long param_1,int param_2)

{
  int local_10;
  int local_c;
  
  local_10 = 0;
  do {
    if (param_2 <= local_10) {
      return 0;
    }
    for (local_c = 0; local_c < param_2; local_c = local_c + 1) {
      if ((*(int *)(param_1 + (long)local_10 * 4) == *(int *)(param_1 + (long)local_c * 4)) &&
         (local_10 != local_c)) {
        return 0xffffffff;
      }
    }
    local_10 = local_10 + 1;
  } while( true );
}


undefined8 check_order_stack(int *param_1)

{
  int local_c;
  
  local_c = param_1[10];
  while( true ) {
    if (*param_1 <= local_c) {
      return 0;
    }
    if (*(int *)(*(long *)(param_1 + 4) + (long)local_c * 4) !=
        *(int *)(*(long *)(param_1 + 0x14) + (long)local_c * 4)) break;
    local_c = local_c + 1;
  }
  return 0xffffffff;
}

void check_top_both_stacks(long param_1)

{
  if (*(int *)(((long)*(int *)(param_1 + 0x28) + 1) * 4 + *(long *)(param_1 + 0x10)) <
      *(int *)((long)*(int *)(param_1 + 0x28) * 4 + *(long *)(param_1 + 0x10))) {
    operation(param_1,&DAT_001055da);
    swap_operations(param_1,&DAT_001055da);
  }
  if (*(int *)((long)*(int *)(param_1 + 0x2c) * 4 + *(long *)(param_1 + 0x18)) <
      *(int *)(((long)*(int *)(param_1 + 0x2c) + 1) * 4 + *(long *)(param_1 + 0x18))) {
    operation(param_1,&DAT_001055de);
    swap_operations(param_1,&DAT_001055de);
  }
  return;

int checkless(long param_1,int param_2,int param_3,int param_4)

{
  int local_c;
  
  local_c = param_2;
  while( true ) {
    if (param_3 <= local_c) {
      return -1;
    }
    if (*(int *)(param_1 + (long)local_c * 4) <= param_4) break;
    local_c = local_c + 1;
  }
  return local_c;
}

int checkmore(long param_1,int param_2,int param_3,int param_4)

{
  int local_c;
  
  local_c = param_2;
  while( true ) {
    if (param_3 <= local_c) {
      return -1;
    }
    if (param_4 < *(int *)(param_1 + (long)local_c * 4)) break;
    local_c = local_c + 1;
  }
  return local_c;
}

int column_a(long param_1,int param_2)

{
  int iVar1;
  int local_10;
  
  iVar1 = nblen(*(undefined4 *)(*(long *)(param_1 + 0x10) + (long)param_2 * 4));
  if ((*(int *)(param_1 + 0x30) == *(int *)(*(long *)(param_1 + 0x10) + (long)param_2 * 4)) &&
     (*(int *)(param_1 + 0x28) <= param_2)) {
    ft_putstr("|     * ");
  }
  else {
    ft_putstr("|       ");
  }
  ft_putnbr(*(undefined4 *)(*(long *)(param_1 + 0x10) + (long)param_2 * 4));
  local_10 = 0xb - iVar1;
  while( true ) {
    if (local_10 == 0) break;
    ft_putchar(0x20);
    local_10 = local_10 + -1;
  }
  return param_2;
}

int column_b(long param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int local_10;
  
  iVar1 = nblen(*(undefined4 *)(*(long *)(param_1 + 0x18) + (long)param_2 * 4));
  iVar2 = is_pibon(*(undefined8 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x48),
                   *(undefined4 *)(*(long *)(param_1 + 0x18) + (long)param_2 * 4));
  if ((iVar2 == 1) && (*(int *)(param_1 + 0x2c) <= param_2)) {
    ft_putstr("|     * ");
  }
  else {
    ft_putstr("|       ");
  }
  ft_putnbr(*(undefined4 *)(*(long *)(param_1 + 0x18) + (long)param_2 * 4));
  local_10 = 0xb - iVar1;
  while( true ) {
    if (local_10 == 0) break;
    ft_putchar(0x20);
    local_10 = local_10 + -1;
  }
  ft_putendl(&DAT_0010563d);
  return param_2;
}

long copy_inttab(long param_1,long param_2,int param_3,int param_4)

{
  undefined4 local_c;
  
  for (local_c = 0; local_c < (param_4 - param_3) + 1; local_c = local_c + 1) {
    *(undefined4 *)(param_2 + (long)local_c * 4) =
         *(undefined4 *)(param_1 + (long)(local_c + param_3) * 4);
  }
  return param_2;
}

int count_argnb(undefined8 param_1)

{
  int iVar1;
  long lVar2;
  int local_18;
  int local_14;
  
  lVar2 = ft_strsplit(param_1,0x20);
  local_18 = 0;
  local_14 = 0;
  while( true ) {
    if (*(long *)(lVar2 + (long)local_18 * 8) == 0) {
      ft_tabdel(lVar2);
      if (local_14 == 0) {
        local_14 = -1;
      }
      return local_14;
    }
    iVar1 = check_atoi(*(undefined8 *)(lVar2 + (long)local_18 * 8));
    if (iVar1 == -1) break;
    local_14 = local_14 + 1;
    local_18 = local_18 + 1;
  }
  ft_tabdel(lVar2);
  return -1;
}