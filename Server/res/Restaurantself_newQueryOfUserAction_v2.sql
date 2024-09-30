;with cte as
(
  select
    personnel_id as UserId,
		action,
		action_date,
		deviceId,
    rank() over(partition by personnel_id order by action_date asc) as rn
  from serv_user_actions  as bTable
	where
	action in(11,21,31, 41)
	and deviceId = 1
	and
	( action_date <= GETDATE() or action_date is null )
		and
 NOT EXISTS
(
   select personnel_id, deviceId from serv_user_actions as aTable
	 where count_resend > 10
	  and bTable.deviceId = aTable.deviceId
	  and bTable.personnel_id = aTable.personnel_id
) 

​
)
select
UserId,
action
​
from cte
where
rn = 1
​
ORDER BY action_date asc
