use jdzy;
select paper.id as id, paper.title as title, paper_keyword.keyword_id as keyword_id
from paper, paper_keyword
where paper.meet_id=2 
	and paper.publication_year="2007-01-01" 
	and paper_keyword.keyword_id=6
    and paper.id=paper_keyword.paper_id
