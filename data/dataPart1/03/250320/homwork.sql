-- 查询同时拥有两个不同部门,工作经验的员工的姓名
-- 1:
/*
select * 
from employees e
JOIN dept_emp de on e.emp_no = de.emp_no
JOIN departments d on de.dept_no = d.dept_no 
JOIN (select emp_no, count(dept_no) num 
		from dept_emp group by emp_no HAVING num >=2
	 ) info on e.emp_no = info.emp_no
*/

-- 查询每个部门中薪水最高的员工，如果该部门有多个员工薪水相同，则都返回

-- 求每个部门的最高薪水
/*
select max(s.salary), de.dept_no
from salaries s
JOIN dept_emp de on s.emp_no = de.emp_no GROUP by de.dept_no
*/

select e.emp_no, e.first_name, e.last_name, de.dept_no
from employees e
JOIN dept_emp de on e.emp_no = de.emp_no
JOIN salaries s on s.emp_no = e.emp_no
where (dept_no , salary) in (
				select de.dept_no, max(s.salary) 
					from salaries s
					JOIN dept_emp de on s.emp_no = de.emp_no GROUP by de.dept_no
				)







