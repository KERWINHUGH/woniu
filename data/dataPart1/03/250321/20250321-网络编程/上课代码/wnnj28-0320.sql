-- 求员工数：
-- select count(emp_no) from employees

-- 求员工工资总数：
-- select sum(salary) from salaries

-- 求平均数：
--select avg(salary) from salaries

-- 求最大工资数
-- select max(salary) from salaries


-- 求最小工资数
-- select min(salary) from salaries


-- 统计指定部门员工的人数
-- select count(emp_no) from dept_emp where dept_no = 'd003'

-- 统计所有部门员工的人数 , 要包含部门名称   
-- 1: 组函数 5个
-- 2：分组 group by 字段名
-- 3：分组之后的再次筛选  having 
/*
select d.dept_no "部门编号" , d.dept_name "部门名称" ,count(de.emp_no) "员工人数"  
from departments d
left JOIN dept_emp de on de.dept_no = d.dept_no
GROUP by d.dept_no HAVING "员工人数" >= 3
*/
-- insert into departments (dept_no, dept_name) values ('d006', 'IT')

-- 查询每个部门在2020年的总薪水
/*
select de.dept_no, sum(s.salary) 
from salaries s
JOIN dept_emp de on s.emp_no = de.emp_no
AND strftime('%Y', s.to_date) = '2020' 
GROUP by de.dept_no 
*/


-- 日期的处理：
-- 1：得到当前时间：
-- select date();  -- 只有年月日
-- select time();  -- 只有时分秒
-- select datetime();

--  格式化时间：
/*
	%Y		 代表年份
	%m		代表月份
	%d		 代表日期
	%H		代表小时
	%M		代表分钟
	%S		 代表秒
*/
-- select strftime('%Y', '2020-01-30')     -- 隐式转换

-- select strftime('%Y-%m-%d %H:%M:%S', datetime('now'));



-- 子查询 --------------------------------------------------------
-- 请求出最高工资员工的信息

-- 分开写（）
-- select max(salary) from salaries  -- 75000
-- select emp_no from salaries where salary = 75000      -- 2
-- select * from employees where emp_no = 2;

/*
select * from employees 
where emp_no = (select emp_no from salaries where salary = (select min(salary) from salaries))
*/

-- 查询出工资大于50000的员工信息：
-- select * from employees where emp_no in (select emp_no from salaries where salary > 50000 )

-- 请查询出大于平均工资的员工信息（只要员工号）
/*
select e.* , s.salary
from salaries s
join employees e on s.emp_no = e.emp_no
AND s.salary > (select avg(salary) from salaries)
*/
/*
-- 查询返回每个员工信息（名称）及其所在部门（有部门名）的平均工资
select e.emp_no, e.first_name, e.last_name , info.dept_name, info.avg_salary
from employees e
join dept_emp de on e.emp_no = de.emp_no
join (select d.dept_no, d.dept_name, avg(s.salary) avg_salary
		from departments d
		LEFT JOIN dept_emp de on de.dept_no = d.dept_no
		LEFT JOIN salaries s on de.emp_no = s.emp_no  
		GROUP by d.dept_no) info on de.dept_no = info.dept_no


-- 求每个部门的平均工资
select d.dept_no, d.dept_name, avg(s.salary) avg_salary
		from departments d
		LEFT JOIN dept_emp de on de.dept_no = d.dept_no
		LEFT JOIN salaries s on de.emp_no = s.emp_no  
		GROUP by d.dept_no
*/


-- 相关子查询 ------------------------------------------------------------------
-- 相关子查询是依赖于外部查询中的值的子查询。它的执行依赖于外部查询的当前行。

-- 查找工资高于其所在部门平均工资的员工
/*
-- 相关子查询
select de.emp_no, s.salary
from salaries s
join dept_emp de on s.emp_no = de.emp_no
where s.salary > (
			select avg(s02.salary) 
			from salaries s02
			JOIN dept_emp de02 on s02.emp_no = de02.emp_no 
			-- 这里引用了外部的部门编号
			and de02.dept_no = de.dept_no
			)
*/
-- 不使用相关子查询：

select de.emp_no, s.salary
from salaries s
join dept_emp de on s.emp_no = de.emp_no
JOIN ( select avg(salary) avg_salary , de.dept_no
		from salaries s
		JOIN dept_emp de on s.emp_no = de.emp_no
		GROUP by de.dept_no
		)info  on  s.salary > info.avg_salary 
		
and de.dept_no = info.dept_no




			
			
			
/*
-- 每个部门的平均工资 
select avg(salary) 
from salaries s
JOIN dept_emp de on s.emp_no = de.emp_no 
and de.dept_no = 'd003'
*/










