# Minishell
A bash clone (simply)

## Syntax

\<syntax> ::= \<line> | \<line> "|" \<syntax>
<br /><br />

\<line>   ::= \<opt-whitespaces> \<cmd> \<opt-whitespaces>
<br />
|
\<opt-whitespaces> "<" \<opt-whitespaces>  \<file-name> \<line>
<br />
|
\<line> ">"  \<opt-whitespaces> \<file-name> \<opt-whitespaces>
<br /><br />

\<opt-whitespaces> ::= "" | " "  | \<opt-whitespaces>
<br /><br />

\<cmd> ::= \<opt-whitespaces> | \<word> \<opt-whitespaces>  \<flag>
<br /><br />

\<flag> ::= \<opt-whitespaces> \<flag> \<opt-whitespaces> | -\<letter> | -\<word> | \<opt-whitespaces>
.
.
.