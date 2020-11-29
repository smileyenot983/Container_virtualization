FROM ubuntu

RUN apt-get update && apt-get install sysbench -y

COPY my-bash.sh /
RUN chmod +x /my-bash.sh && /my-bash.sh

CMD ["Finished!"]
