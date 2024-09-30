SELECT DISTINCT
AsaController.tags.real_user_fr AS UserId
FROM
AsaController.tags
INNER JOIN AsaController.personnel_access_groups ON AsaController.tags.real_user_fr = AsaController.personnel_access_groups.real_user_fr
INNER JOIN AsaController.access_group_terminals ON AsaController.personnel_access_groups.access_group_fr = AsaController.access_group_terminals.access_group_fr
INNER JOIN AsaController.terminals ON AsaController.access_group_terminals.terminal_fr = AsaController.terminals.id
WHERE
AsaController.tags.archived IS NULL AND
AsaController.terminals.archived IS NULL AND
AsaController.personnel_access_groups.archived IS NULL AND
AsaController.tags.tagId = 5 AND
AsaController.terminals.type = 'UPass' AND
AsaController.terminals.terminalId = %1 AND
AsaController.tags.mainItem = %2
