;with cte as
(
  select
    id,
    action_date,
    real_user_fr,
    terminalId,
		action,
		created_at,
		updated_at,
		count_resend,
    rank() over(partition by real_user_fr order by action_date asc) as rn
  from serv_user_actions as bTable
	where
	action in(11,21,31,41)
	and
	( action_date <= GETDATE() or action_date is null )
	and
 NOT EXISTS
(
   select real_user_fr, terminalId from serv_user_actions as aTable
	 where count_resend > 10
	  and bTable.terminalId = aTable.terminalId
	  and bTable.real_user_fr = aTable.real_user_fr
) 

)
select
id,
action_date,
real_user_fr,
terminalId, 
action,
created_at,
		updated_at,
		count_resend
from cte
where
rn = 1

ORDER BY action_date asc



