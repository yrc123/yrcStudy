use jdzy;
select keyword.id as keyword_id, keyword.keyword as keyword_name,pkeyword.keyword_num as keyword_num 
from
	(select paper_keyword.keyword_id as keyword_id,count(*) as keyword_num
	from paper_keyword
	where paper_id in (select paper.id as paper_id 
						from paper 
						where meet_id=2 and publication_year="2007-01-01"
						group by paper_id)
	group by paper_keyword.keyword_id
	order by keyword_num desc
	limit 10) as pkeyword,keyword
where pkeyword.keyword_id=keyword.id;