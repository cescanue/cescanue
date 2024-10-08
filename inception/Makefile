all:
	@sed "s/BONUS=BONUS/BONUS=MANDATORY/g" ./scrs/.env > tmp; cat tmp > ./scrs/.env; rm tmp
	@mkdir ${HOME}/data >/dev/null 2>&1 || true
	@chmod 777 ${HOME}/data >/dev/null 2>&1 || true
	@mkdir ${HOME}/data/wordpress >/dev/null 2>&1 || true
	@chmod 777 ${HOME}/data/wordpress >/dev/null 2>&1 || true
	@mkdir ${HOME}/data/mysql >/dev/null 2>&1|| true
	@chmod 777 ${HOME}/data/mysql >/dev/null 2>&1 || true
	@docker-compose -f ./scrs/docker-compose.yml up -d --build 

bonus:
	@sed "s/BONUS=MANDATORY/BONUS=BONUS/g" ./scrs/.env > tmp; cat tmp > ./scrs/.env; rm tmp
	@mkdir ${HOME}/data >/dev/null 2>&1 || true
	@chmod 777 ${HOME}/data >/dev/null 2>&1 || true
	@mkdir ${HOME}/data/wordpress >/dev/null 2>&1 || true
	@chmod 777 ${HOME}/data/wordpress >/dev/null 2>&1 || true
	@mkdir ${HOME}/data/mysql >/dev/null 2>&1|| true
	@chmod 777 ${HOME}/data/mysql >/dev/null 2>&1 || true
	@docker-compose -f ./scrs/docker-compose_bonus.yml up -d --build

down:
	@docker-compose -f ./scrs/docker-compose_bonus.yml down

re:
	@docker-compose -f ./scrs/docker-compose.yml up -d --build

clean:
	@docker stop $$(docker ps -qa);\
	docker rm $$(docker ps -qa);\
	docker rmi -f $$(docker images -qa);\
	docker volume rm $$(docker volume ls -q);\
	docker network rm $$(docker network ls --filter name=scrs -q) || true;\

	@rm -rf ${HOME}/data >/dev/null 2>&1 || true
	@rm -rf /home/cescanue/data >/dev/null 2>&1 || true
	
.PHONY: all re down clean