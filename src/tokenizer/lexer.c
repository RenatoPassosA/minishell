/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:47:15 by vide-sou          #+#    #+#             */
/*   Updated: 2025/03/24 11:21:27 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void ft_identify_redirect(char *str, t_sentence_item *item, int len)
{
    if (!ft_strncmp(str, ">", len))
    {
        item->fn = fn_output;
        item->type = type_outfile;
    }
    else if (!ft_strncmp(str, ">>", len))
    {
        item->fn = fn_append;
        item->type = type_outfile;
    }
    else if (!ft_strncmp(str, "<", len))
    {
        item->fn = fn_input;
        item->type = type_infile;
    }
    else if (!ft_strncmp(str, "<<", len))
    {
        item->fn = fn_insert;
        item->type = type_infile;
    }
    else if (!ft_strncmp(str, "=", len))
    {
        item->fn = fn_equal;
        item->type = type_equal;
    }
}

static void ft_identify_groups(char *str, t_sentence_item *item, int len)
{
    if (!ft_strncmp(str, "|", len))
    {
        item->fn = fn_pipe;
        item->type = type_divider;
    }
    else if (!ft_strncmp(str, "&&", len))
    {
        item->fn = fn_and;
        item->type = type_divider;
    }
    else if (!ft_strncmp(str, "||", len))
    {
        item->fn = fn_or;
        item->type = type_divider;
    }
    else if (!ft_strncmp(str, "(", len))
    {
        item->fn = fn_open_parenthesis;
        item->type = type_parenthesis;
    }
    else if (!ft_strncmp(str, ")", len))
    {
        item->fn = fn_close_parenthesis;
        item->type = type_parenthesis;
    }
}

static void ft_identify_item(char *str, t_sentence_item *item)
{
    int     len;

    len = ft_strlen(str);
    item->value = str;
    item->fn = fn_null;
    item->type = type_word;
    ft_identify_redirect(str, item, len);
    ft_identify_groups(str, item, len);
}

t_sentence_item *lexer(char **strs)
{
    int             index;
    t_sentence_item *result;

    index = 0;
    while (strs[index])
        index++;
    result = ft_calloc(index + 1, sizeof(t_sentence_item));
    index = 0;
    while (strs[index])
    {
        ft_identify_item(strs[index], &result[index]);
        index++;
    }
    result[index].value = NULL;
    result[index].fn = fn_null;
    result[index].type = type_word;
    return (result);
}
